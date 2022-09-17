
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

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"


#include "main.h"
#include "lvgl_demo_ui.h"
#include "display_config.h"
#include "uart_config.h"
#include "lora_pingpong.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
hMain_t hMain;
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/


static void main_creatSysteTasks				(void);
static void lvglTimerTask						(void* param);
static void systemLoggerTask					(void* param);
static void main_gpio_config				(void);
const char *MAIN = "Main";
uint8_t logBuffer[RX_BUF_SIZE] = {0};
/* FUNCTION PROTOTYPES -------------------------------------------------------*/


void main_gpio_config(void)
{
	gpio_pad_select_gpio(ON_BOARD_BUTTON);

	gpio_set_direction(ON_BOARD_BUTTON, GPIO_MODE_INPUT);
}

static void lvglTimerTask(void* param)
{
	while(1)
	{
		// The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
		lv_timer_handler();

		vTaskDelay(10/portTICK_PERIOD_MS);
	}
}

static void systemLoggerTask(void* param)
{
	int8_t rssi = 0;
	pingpongMsgId_e messageId = 0;

	while(1)
	{
		if(uartCheckPacketRxFlag())
		{
			//Write log to screen
			uartGetRxBuffer(logBuffer);
			lv_msg_send(MSG_NEW_LOG, logBuffer);
			//dealing with user interface depending on the received values
			messageId = lora_packetDetect(logBuffer);
			//Pingpong response is received. extract the RSSI and send it to the display
			if(PINGPONG_RSSI == messageId)
			{
				lora_getParameter(logBuffer, &rssi);
				_ui_slider_set_property(ui_Slider1, _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM, 100 - rssi);
				//Change the panel color to green to indicate ongoing communication
				_ui_set_panel_color(2);
				//Change connection status and start timeout timer
				hLoraPingPong.pingpong_status.flags.connectionActive = 1;
				hLoraPingPong.timeout = SYS_TICK();
				rssi = 0;
			}
			else if(PINGPONG_RX_TIMEOUT == messageId && hLoraPingPong.pingpong_status.flags.connectionActive)
			{
				_ui_slider_set_property(ui_Slider1, _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM, 100 - rssi);
				_ui_set_panel_color(1);
			}


			uartResetPacketRxFlag();

			memset(logBuffer, 0, RX_BUF_SIZE);
		}
		//Check connection timeout
		if(SYS_TICK() - hLoraPingPong.timeout > LORA_TIMEOUT)
		{
			hLoraPingPong.pingpong_status.flags.connectionActive = 0;
			//set slider to zero
			_ui_slider_set_property(ui_Slider1, _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM, 0);
			_ui_set_panel_color(0);
		}
		if(SYS_TICK() - hMain.mainTimer > 500)
		{
			hMain.main_status.flags.pageChange = 1;
		}

		if(0 == gpio_get_level(ON_BOARD_BUTTON) && hMain.main_status.flags.pageChange)
		{
			changePage();
			hMain.mainTimer = SYS_TICK();
			hMain.main_status.flags.pageChange = 0;
		}


		vTaskDelay(50/portTICK_PERIOD_MS);
	}
}

static void main_creatSysteTasks(void)
{

	xTaskCreatePinnedToCore(lvglTimerTask, "lvgl Timer", 10000, NULL, 4, NULL, 1);

	xTaskCreatePinnedToCore(uart_event_task, "uart event", 10000, NULL, 4, NULL, 1);

	xTaskCreatePinnedToCore(systemLoggerTask, "system log", 1024 * 4, NULL, 4, NULL, 1);
}




/**
 * @brief Program starts from here
 *
 */
void app_main(void)
{

    lvgl_demo_ui(display_config());

    main_gpio_config();

    uart_config();

    main_creatSysteTasks();



}
/**************************  Useful Electronics  ****************END OF FILE***/
