
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  main.h
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Aug 20, 2022
 * @brief   		:
 *
 ******************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_


/* INCLUDES ------------------------------------------------------------------*/
#include "display_config.h"
#include "gpio_ui.h"
/* MACROS --------------------------------------------------------------------*/
//#define ON_BOARD_BUTTON         GPIO_NUM_14
#define SYS_TICK()				xTaskGetTickCount() * portTICK_PERIOD_MS
/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef struct
{
	uint32_t mainTimer;
	union
	{
		uint8_t all;
		struct
		{
			uint8_t reserved	:7,
					pageChange	:1;
		}flags;
	}main_status;
}hMain_t;
/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
//lv_obj_t * display_config				(void);


#endif /* MAIN_MAIN_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
