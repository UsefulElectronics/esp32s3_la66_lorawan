
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  gpio_ui.h
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Sep 27, 2022
 * @brief   		:
 *
 ******************************************************************************/

#ifndef MAIN_GPIO_UI_H_
#define MAIN_GPIO_UI_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
/* MACROS --------------------------------------------------------------------*/
#define ENABLE		1
#define DISABLE		0

#define GPIO_SET	1
#define GPIO_RESET	0

#define ON_BOARD_BUTTON         GPIO_NUM_14
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
extern SemaphoreHandle_t button_sem;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void gpioIntConfig(uint8_t gpioNum);
void gpioIsrHandler(void *arg);

#endif /* MAIN_GPIO_UI_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
