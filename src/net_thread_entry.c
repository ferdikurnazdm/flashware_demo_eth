#include <net_thread.h>
#include <string.h>
#include <stdbool.h>

/* Aynı anda bekleyebilecek bağlantı sayısı */
#define BACKLOG_COUNT   5

/* TCP veri alma buffer boyutu */
#define BUF_SIZE        256

/* TCP server port */
#define SERVER_PORT     9999

/* Statik IP ayarları */
const uint8_t ucIPAddress[4]        = {192, 168, 1, 118};
const uint8_t ucNetMask[4]          = {255, 255, 255, 0};
const uint8_t ucGatewayAddress[4]   = {192, 168, 1, 1};
const uint8_t ucDNSServerAddress[4] = {192, 168, 1, 1};

/* Ethernet MAC adresi */
const uint8_t ucMACAddress[6]       = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};

/* Job thread'e gönderilecek komut tipi, (Yeni eklendi). */
typedef enum
{
    INPUT_CMD_OFF = 0,
    INPUT_CMD_ON
} input_cmd_t;

/*
 * g_input_queue daha önce oluşturulduğu için burada extern kullanıyoruz.
 * Queue oluşturma işlemi FSP configurator veya başka dosyada olmalı.(Yeni eklendi)
 */
extern QueueHandle_t g_input_queue;

/* Server socket */
Socket_t xSocket;

/* Client socket */
Socket_t xClientSocket;

/* Server bind adres yapısı */
struct freertos_sockaddr xBindAddress;

/* Client adres bilgisi */
struct freertos_sockaddr xClientAddress;

/* Client adres uzunluğu */
socklen_t xClientAddressLength;

/* Network hazır bilgisi */
volatile bool network_up = false;

/*
 * IP stack network durum callback'i
 * Eğer bu fonksiyon başka dosyada zaten varsa buradan kaldır.
 */
void vApplicationIPNetworkEventHook(eIPCallbackEvent_t eNetworkEvent)
{
    if (eNetworkEvent == eNetworkUp)
    {
        network_up = true;
    }
    else
    {
        network_up = false;
    }
}

/* Gelen string sonundaki \r \n ve boşluk karakterlerini siler. */
static void trim_command(char *str)
{
    int len = (int) strlen(str);

    while (len > 0)
    {
        if ((str[len - 1] == '\r') ||
            (str[len - 1] == '\n') ||
            (str[len - 1] == ' '))
        {
            str[len - 1] = '\0';
            len--;
        }
        else
        {
            break;
        }
    }
}

/*
 * Client ile haberleşme fonksiyonu
 * Burada gelen on/off mesajı queue üzerinden job_thread'e gönderilir.(Mesajlar da düzenleme yapıldı).
 */
static void handle_client_connection(void)
{
    char pcRxBuffer[BUF_SIZE];

    BaseType_t lBytes;
    BaseType_t xSentBytes;

    TickType_t xReceiveTimeOut = portMAX_DELAY;
    TickType_t xSendTimeOut    = pdMS_TO_TICKS(1000);

    const char *welcomeMessage = "Baglanti kuruldu. Komutlar: on / off\r\n";

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

        lBytes = FreeRTOS_recv(xClientSocket,
                               pcRxBuffer,
                               BUF_SIZE - 1,
                               0);

        if (lBytes > 0)
        {
            pcRxBuffer[lBytes] = '\0';

            trim_command(pcRxBuffer);

            input_cmd_t cmd;
            const char *replyMessage;

            if ((strcmp(pcRxBuffer, "on") == 0) ||
                (strcmp(pcRxBuffer, "ON") == 0))
            {
                cmd = INPUT_CMD_ON;

                if (xQueueSend(g_input_queue,
                               &cmd,
                               pdMS_TO_TICKS(100)) == pdTRUE)
                {
                    replyMessage = "OK: LED ON komutu job_thread'e gonderildi\r\n";
                }
                else
                {
                    replyMessage = "ERROR: Queue dolu, komut gonderilemedi\r\n";
                }
            }
            else if ((strcmp(pcRxBuffer, "off") == 0) ||
                     (strcmp(pcRxBuffer, "OFF") == 0))
            {
                cmd = INPUT_CMD_OFF;

                if (xQueueSend(g_input_queue,
                               &cmd,
                               pdMS_TO_TICKS(100)) == pdTRUE)
                {
                    replyMessage = "OK: LED OFF komutu job_thread'e gonderildi\r\n";
                }
                else
                {
                    replyMessage = "ERROR: Queue dolu, komut gonderilemedi\r\n";
                }
            }
            else
            {
                replyMessage = "ERROR: sadece on veya off gonder\r\n";
            }

            xSentBytes = FreeRTOS_send(xClientSocket,
                                       replyMessage,
                                       strlen(replyMessage),
                                       0);

            if (xSentBytes <= 0)
            {
                break;
            }
        }
        else if (lBytes == 0)
        {
            break;
        }
        else
        {
            break;
        }
    }
}

/*
 * FreeRTOS tarafından çağrılan net_thread ana fonksiyonu.
 */
void net_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    BaseType_t status;

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

    if (FreeRTOS_listen(xSocket, BACKLOG_COUNT) != 0)
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
            handle_client_connection();

            FreeRTOS_shutdown(xClientSocket, FREERTOS_SHUT_RDWR);
            FreeRTOS_closesocket(xClientSocket);

            xClientSocket = FREERTOS_INVALID_SOCKET;
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}
