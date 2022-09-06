
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  main1.c
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Aug 20, 2022
 * @brief   		:
 *
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
//#include "esp_lcd_panel_io.h"
//#include "esp_lcd_panel_vendor.h"
//#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"


#include "main.h"
#include "lvgl_demo_ui.h"
#include "display_config.h"
#include "uart_config.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/

/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/


static void main_creatSysteTasks				(void);
static void lvglTimerTask						(void* param);


/* FUNCTION PROTOTYPES -------------------------------------------------------*/




static void lvglTimerTask(void* param)
{
	while(1)
	{
		// The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
		lv_timer_handler();

		vTaskDelay(10/portTICK_PERIOD_MS);
	}
}

static void main_creatSysteTasks(void)
{

	xTaskCreatePinnedToCore(lvglTimerTask, "lvgl Timer", 10000, NULL, 4, NULL, 1);

	xTaskCreatePinnedToCore(uart_event_task, "uart event", 10000, NULL, 4, NULL, 1);
}




/**
 * @brief Program starts from here
 *
 */
void app_main(void)
{


    lvgl_demo_ui(display_config());

    uart_config();

    main_creatSysteTasks();

}
/**************************  Useful Electronics  ****************END OF FILE***/
