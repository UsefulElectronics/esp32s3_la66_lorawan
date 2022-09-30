
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  la66.h
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Sep 30, 2022
 * @brief   		:
 *
 ******************************************************************************/

#ifndef MAIN_LA66_H_
#define MAIN_LA66_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
/* MACROS --------------------------------------------------------------------*/
#define AT_NETWORK_JOINED			"JOINED"
#define AT_MODULE_RESET 			"ATZ"
#define AT_APPLICATION_EUI			"AT+APPEUI"
#define AT_APPLICATION_KEY			"AT+APPKEY"
#define AT_APPLICATION_SESSION_KEY	"AT+APPSKEY"

#define AT_APPLICATION_PORT			"AT+PORT"
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/



#endif /* MAIN_LA66_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
