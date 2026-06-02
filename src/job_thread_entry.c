/* Yeni thread olarak job_thread eklendi. */
#include "job_thread.h"

#define DEBUG_LED_PIN   BSP_IO_PORT_02_PIN_10   // P210

typedef enum
{
    INPUT_CMD_OFF = 0,
    INPUT_CMD_ON
} input_cmd_t;

extern QueueHandle_t g_input_queue;

void job_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    input_cmd_t received_cmd;

    /* Başlangıçta LED kapalı olsun */
    R_IOPORT_PinWrite(&g_ioport_ctrl,
                      DEBUG_LED_PIN,
                      BSP_IO_LEVEL_LOW);

    while (1)
    {
        if (xQueueReceive(g_input_queue,
                          &received_cmd,
                          portMAX_DELAY) == pdTRUE)
        {
            if (received_cmd == INPUT_CMD_ON)
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl,
                                  DEBUG_LED_PIN,
                                  BSP_IO_LEVEL_HIGH);
            }
            else if (received_cmd == INPUT_CMD_OFF)
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl,
                                  DEBUG_LED_PIN,
                                  BSP_IO_LEVEL_LOW);
            }
        }
    }
}
