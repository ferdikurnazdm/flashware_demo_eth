/******************************************************************************
 *
 * JOB THREAD - KOMUT KONTROL VE FAKTÖRİYEL HESAPLAMA
 *
 * Bu thread uygulamanın iş mantığını (business logic) gerçekleştirir.
 *
 * Görevleri:
 * 1- net_thread'den gelen TCP komutunu alır.
 * 2- Komutu temizler (CR/LF ve boşluk karakterleri silinir).
 * 3- Girilen verinin geçerli bir sayı olup olmadığını kontrol eder.
 * 4- Sayı geçerliyse faktöriyel hesaplar.
 * 5- Sonucu g_output_queue üzerinden net_thread'e gönderir.
 *
 * TCP haberleşmesi burada yapılmaz.
 * Socket işlemleri sadece net_thread içerisindedir.
 *
 ******************************************************************************/

#include "job_thread.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define RESULT_TEXT_SIZE   256
#define MAX_DIGITS         200

/* Queue'lar net_thread tarafından da kullanılmaktadır */
extern QueueHandle_t g_input_queue;
extern QueueHandle_t g_output_queue;

/******************************************************************************
 *
 * trim_command()
 *
 * TCP üzerinden gelen komutların sonunda oluşabilecek:
 * - '\r'
 * - '\n'
 * - ' '
 *
 * karakterlerini temizler.
 *
 * Örnek:
 * "25\r\n" -> "25"
 *
 ******************************************************************************/

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

/******************************************************************************
 *
 * parse_number()
 *
 * Girilen komutun sadece rakamlardan oluşup oluşmadığını kontrol eder.
 *
 * Geçerli:
 *   "5"
 *   "123"
 *
 * Geçersiz:
 *   "-5"
 *   "abc"
 *   "12a"
 *
 * Başarılı olursa:
 *   number değişkenine sonucu yazar
 *   true döndürür
 *
 * Hata olursa:
 *   false döndürür
 *
 ******************************************************************************/

static bool parse_number(char *str, uint32_t *number)
{
    if ((str == NULL) || (number == NULL) || (strlen(str) == 0))
    {
        return false;
    }

    for (uint32_t i = 0; i < strlen(str); i++)
    {
        if ((str[i] < '0') || (str[i] > '9'))
        {
            return false;
        }
    }

    *number = (uint32_t) atoi(str);

    return true;
}

/******************************************************************************
 *
 * factorial_to_string()
 *
 * Büyük sayılar için faktöriyel hesabı yapar.
 *
 * uint64_t yerine büyük sayı algoritması kullanılır.
 *
 * Örnek:
 * 20! = 2432902008176640000
 * 50! = 30414093201713378043612608166064768844377641568960512000000000000
 *
 * Sonuç ASCII karakter dizisi olarak üretilir.
 *
 * Eğer sonuç MAX_DIGITS sınırını aşarsa:
 * "ERROR: sonuc cok buyuk"
 * mesajı oluşturulur.
 *
 ******************************************************************************/

static void factorial_to_string(uint32_t n,
                                char *out,
                                uint32_t out_size)
{
    uint8_t digits[MAX_DIGITS];
    uint32_t digit_count = 1;

    memset(digits, 0, sizeof(digits));

    /* Başlangıç değeri 1 */
    digits[0] = 1;

    /*
     * Büyük sayı çarpma algoritması
     */
    for (uint32_t i = 2; i <= n; i++)
    {
        uint32_t carry = 0;

        for (uint32_t j = 0; j < digit_count; j++)
        {
            uint32_t value = ((uint32_t) digits[j] * i) + carry;

            digits[j] = (uint8_t) (value % 10);
            carry = value / 10;
        }

        /*
         * Carry değerlerini yeni basamaklara ekle
         */
        while (carry > 0)
        {
            if (digit_count >= MAX_DIGITS)
            {
                snprintf(out,
                         out_size,
                         "ERROR: sonuc cok buyuk\r\n");
                return;
            }

            digits[digit_count] = (uint8_t) (carry % 10);
            carry = carry / 10;
            digit_count++;
        }
    }

    uint32_t index = 0;

    /*
     * Sonuç başlığı oluşturulur.
     *
     * Örnek:
     * 10! =
     */
    int written = snprintf(out + index,
                           out_size - index,
                           "%lu! = ",
                           (unsigned long) n);

    if (written > 0)
    {
        index += (uint32_t) written;
    }

    /*
     * Basamaklar ters tutulduğu için
     * tersten yazdırılır.
     */
    for (int32_t i = (int32_t) digit_count - 1; i >= 0; i--)
    {
        if (index < (out_size - 3))
        {
            out[index] = (char) (digits[i] + '0');
            index++;
        }
        else
        {
            break;
        }
    }

    out[index++] = '\r';
    out[index++] = '\n';
    out[index] = '\0';
}

/******************************************************************************
 *
 * job_thread_entry()
 *
 * Thread'in ana çalışma döngüsü.
 *
 * İş Akışı:
 *
 * net_thread
 *     |
 *     v
 * g_input_queue
 *     |
 *     v
 * job_thread
 *     |
 *     v
 * g_output_queue
 *     |
 *     v
 * net_thread
 *
 ******************************************************************************/

void job_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    char request_text[RESULT_TEXT_SIZE];
    char result_text[RESULT_TEXT_SIZE];

    uint32_t request_number = 0;

    while (1)
    {
        memset(request_text, 0, sizeof(request_text));
        memset(result_text, 0, sizeof(result_text));

        request_number = 0;

        /*
         * net_thread'den gelen komut beklenir.
         * Queue boş ise thread bloklanır.
         */
        if (xQueueReceive(g_input_queue,
                          request_text,
                          portMAX_DELAY) == pdTRUE)
        {
            /*
             * TCP komut sonundaki CR/LF karakterlerini temizle.
             */
            trim_command(request_text);

            /*
             * Kullanıcının gönderdiği veri geçerli sayı mı?
             */
            if (parse_number(request_text, &request_number) == false)
            {
                snprintf(result_text,
                         sizeof(result_text),
                         "ERROR: sadece pozitif tam sayi gonderin\r\n");
            }
            else
            {
                /*
                 * Faktöriyel hesabını gerçekleştir.
                 */
                factorial_to_string(request_number,
                                    result_text,
                                    sizeof(result_text));
            }

            /*
             * Oluşturulan cevabı net_thread'e gönder.
             */
            xQueueSend(g_output_queue,
                       result_text,
                       pdMS_TO_TICKS(100));
        }
    }
}
