
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  uart.c
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Sep 5, 2022
 * @brief   		:
 *
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "uart_config.h"

/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
static QueueHandle_t uart_queue;
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/
const char *UART_DEBUG = "UART";
/* FUNCTION PROTOTYPES -------------------------------------------------------*/
void uart_config(void)
{
    const uart_config_t uart_config =
    {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(UART_AT_PORT, RX_BUF_SIZE * 2, TX_BUF_SIZE * 2, 20, &uart_queue, 0);
    uart_param_config(UART_AT_PORT, &uart_config);
    uart_set_pin(UART_AT_PORT, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    //Set uart pattern detect function.
    uart_enable_pattern_det_baud_intr(UART_AT_PORT, '\n', PATTERN_AT_COUNT, 2, 0, 0);
    //Reset the pattern queue length to record at most 20 pattern positions.
    uart_pattern_queue_reset(UART_AT_PORT, 100);
}

void uart_event_task(void *pvParameters)
{
    uart_event_t event;
    size_t buffered_size;
    uint8_t* dtmp = (uint8_t*) malloc(RX_BUF_SIZE);
    for(;;)
    {
        //Waiting for UART event.
        if(xQueueReceive(uart_queue, (void * )&event, (portTickType)portMAX_DELAY))
        {
            bzero(dtmp, RX_BUF_SIZE);

            switch(event.type)
            {
                //Event of UART receving data
                /*We'd better handler data event fast, there would be much more data events than
                other types of events. If we take too much time on data event, the queue might
                be full.*/
                case UART_DATA:
                    ESP_LOGI(UART_DEBUG, "[UART DATA]: %d", event.size);
                    uart_read_bytes(UART_AT_PORT, dtmp, event.size, portMAX_DELAY);
                    ESP_LOGI(UART_DEBUG, "%s",dtmp);
                    ESP_LOGI(UART_DEBUG, "[DATA EVT]:");

                    break;
                //Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    ESP_LOGI(UART_DEBUG, "hw fifo overflow");
                    // If fifo overflow happened, you should consider adding flow control for your application.
                    // The ISR has already reset the rx FIFO,
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(UART_AT_PORT);
                    xQueueReset(uart_queue);
                    break;
                //Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(UART_DEBUG, "ring buffer full");
                    // If buffer full happened, you should consider encreasing your buffer size
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(UART_AT_PORT);
                    xQueueReset(uart_queue);
                    break;

                //UART_PATTERN_DET
                case UART_PATTERN_DET:
                    uart_get_buffered_data_len(UART_AT_PORT, &buffered_size);
                    int pos = uart_pattern_pop_pos(UART_AT_PORT);
                    ESP_LOGI(UART_DEBUG, "[UART PATTERN DETECTED] pos: %d, buffered size: %d", pos, buffered_size);
                    if (pos == -1) {
                        // There used to be a UART_PATTERN_DET event, but the pattern position queue is full so that it can not
                        // record the position. We should set a larger queue size.
                        // As an example, we directly flush the rx buffer here.
                        uart_flush_input(UART_AT_PORT);
                    } else {
                        uart_read_bytes(UART_AT_PORT, dtmp, pos, 100 / portTICK_PERIOD_MS);
                        uint8_t pat[PATTERN_AT_COUNT + 1];
                        memset(pat, 0, sizeof(pat));
                        uart_read_bytes(UART_AT_PORT, pat, PATTERN_AT_COUNT, 100 / portTICK_PERIOD_MS);
                        ESP_LOGI(UART_DEBUG, "read data: %s", dtmp);
                        ESP_LOGI(UART_DEBUG, "read pat : %s", pat);
                    }
                    break;
                //Others
                default:
                    ESP_LOGI(UART_DEBUG, "uart event type: %d", event.type);
                    break;
            }
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

/**************************  Useful Electronics  ****************END OF FILE***/
