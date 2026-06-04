/******************************************************************************
 *
 * TCP FACTORIAL SERVER - NET THREAD
 *
 * Bu thread sadece TCP haberleşmesinden sorumludur.
 *
 * İş Akışı:
 * 1- TCP server oluşturulur.
 * 2- Client bağlantısı beklenir.
 * 3- Client'tan gelen komut alınır.
 * 4- Gelen komut g_input_queue üzerinden job_thread'e gönderilir.
 * 5- job_thread sonucu hesaplar ve g_output_queue'ye yazar.
 * 6- Sonuç tekrar TCP client'a gönderilir.
 *
 * Hesaplama işlemleri burada yapılmaz.
 * Hesaplama tamamen job_thread içerisindedir.
 *
 ******************************************************************************/

#include <net_thread.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#define BACKLOG_COUNT      5
#define BUF_SIZE           256
#define SERVER_PORT        9999
#define RESULT_TEXT_SIZE   256

#define DEBUG_LED_PIN      BSP_IO_PORT_02_PIN_10 //P200 pini
#define DEBUG_LED_ON   true
#define DEBUG_LED_OFF  false

extern QueueHandle_t g_input_queue;
extern QueueHandle_t g_output_queue;

const uint8_t ucIPAddress[4]        = {192, 168, 1, 118};
const uint8_t ucNetMask[4]          = {255, 255, 255, 0};
const uint8_t ucGatewayAddress[4]   = {192, 168, 1, 1};
const uint8_t ucDNSServerAddress[4] = {192, 168, 1, 1};
const uint8_t ucMACAddress[6]       = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};

Socket_t xSocket;
Socket_t xClientSocket;

struct freertos_sockaddr xBindAddress;
struct freertos_sockaddr xClientAddress;
socklen_t xClientAddressLength;

volatile bool network_up = false;

/******************************************************************************
 *
 * FreeRTOS+TCP tarafından çağrılır.
 *
 * Ethernet link ve IP durumunu takip etmek için kullanılır.
 * Network ayağa kalktığında network_up=true olur.
 *
 ******************************************************************************/

void vApplicationIPNetworkEventHook(eIPCallbackEvent_t eNetworkEvent)
{
    network_up = (eNetworkEvent == eNetworkUp);
}


/******************************************************************************
 *
 * Debug amaçlı LED kontrol fonksiyonu
 *
 * state = true  -> LED ON
 * state = false -> LED OFF
 *
 ******************************************************************************/

static void debug_led_set(bool state)
{
    R_IOPORT_PinWrite(&g_ioport_ctrl,
                      DEBUG_LED_PIN,
                      state ?
                      BSP_IO_LEVEL_HIGH :
                      BSP_IO_LEVEL_LOW);
}

/******************************************************************************
 *
 * Bağlanan TCP client ile haberleşmeyi yönetir.
 *
 * Görevleri:
 * - Karşılama mesajı gönderir
 * - Gelen TCP verisini okur
 * - Veriyi job_thread'e iletir
 * - Sonucu bekler
 * - Sonucu client'a geri gönderir
 *
 * Client bağlantısı kapanana kadar döngü devam eder.
 *
 ******************************************************************************/

static void handle_client_connection(void)
{
    char pcRxBuffer[BUF_SIZE];
    char result_text[RESULT_TEXT_SIZE];

    BaseType_t lBytes;
    BaseType_t xSentBytes;

    TickType_t xReceiveTimeOut = portMAX_DELAY;
    TickType_t xSendTimeOut    = pdMS_TO_TICKS(1000);

    const char *welcomeMessage =
        "Baglanti kuruldu. Faktoriyel icin tam sayi gonderin\r\n";

    FreeRTOS_setsockopt(xClientSocket,
                        0,
                        FREERTOS_SO_RCVTIMEO,
                        &xReceiveTimeOut,
                        sizeof(xReceiveTimeOut));

    FreeRTOS_setsockopt(xClientSocket,
                        0,
                        FREERTOS_SO_SNDTIMEO,
                        &xSendTimeOut,
                        sizeof(xSendTimeOut));

    FreeRTOS_send(xClientSocket,
                  welcomeMessage,
                  strlen(welcomeMessage),
                  0);

    while (1)
    {
        memset(pcRxBuffer, 0, sizeof(pcRxBuffer));
        memset(result_text, 0, sizeof(result_text));

        lBytes = FreeRTOS_recv(xClientSocket,
                               pcRxBuffer,
                               BUF_SIZE - 1,
                               0);
        /*
         * Client'tan veri alınır.
         *
         * Dönen değer:
         * >0 : Alınan byte sayısı
         *  0 : Bağlantı kapandı
         * <0 : Hata oluştu
         */

        if (lBytes <= 0)
        {
            break;
        }

        pcRxBuffer[lBytes] = '\0';

        /*
         * TCP'den gelen ham komut doğrudan job_thread'e gönderilir.
         *
         * Örnek:
         * Client --> "5"
         * Client --> "FACTORIAL 5"
         * Client --> "HELP"
         *
         * Komutun anlamlandırılması job_thread tarafından yapılır.
         */

        if (xQueueSend(g_input_queue,
                       pcRxBuffer,
                       pdMS_TO_TICKS(100)) != pdTRUE)
        {
            const char *queueError =
                "ERROR: g_input_queue dolu\r\n";

            FreeRTOS_send(xClientSocket,
                          queueError,
                          strlen(queueError),
                          0);

            continue;
        }
        /*
         * job_thread'den cevap beklenir.
         *
         * Maksimum bekleme süresi:
         * 5000 ms
         *
         * Eğer cevap gelmezse timeout hatası client'a gönderilir.
         */
        if (xQueueReceive(g_output_queue,
                          result_text,
                          pdMS_TO_TICKS(5000)) == pdTRUE)
        {
            xSentBytes = FreeRTOS_send(xClientSocket,
                                       result_text,
                                       strlen(result_text),
                                       0);
        }
        else
        {
            const char *timeoutError =
                "ERROR: job_thread cevap vermedi\r\n";

            xSentBytes = FreeRTOS_send(xClientSocket,
                                       timeoutError,
                                       strlen(timeoutError),
                                       0);
        }

        if (xSentBytes <= 0)
        {
            break;
        }
    }
}

/******************************************************************************
 *
 * NET THREAD ANA GÖREVİ
 *
 * Görev sırası:
 *
 * 1- FreeRTOS+TCP stack başlatılır
 * 2- Ethernet/IP hazır olana kadar beklenir
 * 3- TCP server socket oluşturulur
 * 4- Port 9999'a bind edilir
 * 5- Listen durumuna alınır
 * 6- Client bağlantıları kabul edilir
 * 7- Her client için handle_client_connection() çağrılır
 *
 ******************************************************************************/

void net_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    BaseType_t status;

    debug_led_set(DEBUG_LED_OFF);

    status = FreeRTOS_IPInit(ucIPAddress,
                             ucNetMask,
                             ucGatewayAddress,
                             ucDNSServerAddress,
                             ucMACAddress);

    if (status == pdFALSE)
    {
        __BKPT(0);
    }

    while (network_up == false)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    /*
     * Yeni TCP bağlantısı beklenir.
     *
     * Başarılı olursa:
     * - Debug LED yakılır
     * - Client haberleşmesi başlatılır
     *
     * Bağlantı sonlanınca:
     * - Socket kapatılır
     * - Debug LED söndürülür
     */
    xSocket = FreeRTOS_socket(FREERTOS_AF_INET,
                              FREERTOS_SOCK_STREAM,
                              FREERTOS_IPPROTO_TCP);

    if (xSocket == FREERTOS_INVALID_SOCKET)
    {
        __BKPT(0);
    }

    memset(&xBindAddress, 0, sizeof(xBindAddress));

    xBindAddress.sin_family = FREERTOS_AF_INET;
    xBindAddress.sin_addr   = 0;
    xBindAddress.sin_port   = FreeRTOS_htons(SERVER_PORT);

    if (FreeRTOS_bind(xSocket,
                      &xBindAddress,
                      sizeof(xBindAddress)) != 0)
    {
        __BKPT(0);
    }

    if (FreeRTOS_listen(xSocket,
                        BACKLOG_COUNT) != 0)
    {
        __BKPT(0);
    }

    while (1)
    {
        xClientAddressLength = sizeof(xClientAddress);

        xClientSocket = FreeRTOS_accept(xSocket,
                                        &xClientAddress,
                                        &xClientAddressLength);

        if (xClientSocket != FREERTOS_INVALID_SOCKET)
        {
            debug_led_set(DEBUG_LED_ON);

            handle_client_connection();
            /*
             * Client bağlantısını düzgün şekilde sonlandır.
             *
             * Önce shutdown:
             * - TCP FIN gönderilir
             *
             * Sonra socket kapatılır.
             */
            FreeRTOS_shutdown(xClientSocket,
                              FREERTOS_SHUT_RDWR);


            FreeRTOS_closesocket(xClientSocket);

            xClientSocket = FREERTOS_INVALID_SOCKET;

            debug_led_set(DEBUG_LED_OFF);


        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}
