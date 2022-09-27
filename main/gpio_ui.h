
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
#include "driver/gpio.h"
/* MACROS --------------------------------------------------------------------*/

/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
extern SemaphoreHandle_t button_sem;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void gpioIntConfig(uint8_t gpioNum);
void gpioIsrHandler(void *arg);

#endif /* MAIN_GPIO_UI_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
