
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
#include "driver/uart.h"
#include "driver/gpio.h"
/* MACROS --------------------------------------------------------------------*/
#define TXD_PIN 	(GPIO_NUM_4)
#define RXD_PIN 	(GPIO_NUM_5)

#define RX_BUF_SIZE	1024
#define TX_BUF_SIZE	1024
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void uart_config	(void);


#endif /* MAIN_UART_CONFIG_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
