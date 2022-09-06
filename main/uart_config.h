
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  uart.h
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Sep 5, 2022
 * @brief   		:
 *
 ******************************************************************************/

#ifndef MAIN_UART_CONFIG_H_
#define MAIN_UART_CONFIG_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "driver/gpio.h"
/* MACROS --------------------------------------------------------------------*/
#define TXD_PIN 			(GPIO_NUM_12)
#define RXD_PIN 			(GPIO_NUM_13)

#define UART_AT_PORT 		UART_NUM_0
#define PATTERN_AT_COUNT    2

#define RX_BUF_SIZE			1024
#define TX_BUF_SIZE			1024
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void uart_config	(void);
void uart_event_task(void *pvParameters);

#endif /* MAIN_UART_CONFIG_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
