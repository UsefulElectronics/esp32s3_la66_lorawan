
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
static void main_gpio_config					(void);
static void main_loggerHandler					(uint8_t* logBuffer);
const char *MAIN = "Main";
uint8_t logBuffer[RX_BUF_SIZE] = {0};
/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief 	This functions keeps the previous logs saved in a static buffer to replace them later on in the main logger buffer
 * 			shifted downwards.
 *
 * @param 	logBuffer	: Main log buffer pointer.
 */
static void main_loggerHandler(uint8_t* logBuffer)
{
	static char logCopy[RX_BUF_SIZE] = {0};
	char tempLog[RX_BUF_SIZE] = {0};
	uint16_t receivedStringSize = strlen((char*) logBuffer);
	memcpy(tempLog, logCopy, RX_BUF_SIZE);
	memcpy(logCopy, logBuffer, RX_BUF_SIZE);
	//combine the new and the old logs
	memcpy(logCopy + receivedStringSize, tempLog, RX_BUF_SIZE - receivedStringSize);
	memcpy(logBuffer, logCopy, RX_BUF_SIZE);
}

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
	pingpongType_e pingpongId = 0;
	char panelString[30] = {0};

	while(1)
	{
		if(xSemaphoreTake(UART_RXsem, portMAX_DELAY) == pdTRUE)
		{
			if(uartCheckPacketRxFlag())
			{
				//Write log to screen
				uartGetRxBuffer(logBuffer);
//				ESP_LOGI(MAIN, "%s",logBuffer);
				main_loggerHandler(logBuffer);
				lv_msg_send(MSG_NEW_LOG, logBuffer);
				//dealing with user interface depending on the received values
				messageId = lora_packetDetect(logBuffer);
				//Pingpong response is received. extract the RSSI and send it to the display
				if(PINGPONG_RSSI == messageId)
				{
					lora_getParameter(logBuffer, &rssi);
					_ui_slider_set_property(ui_Slider1, _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM, 100 - rssi);
					//Change the panel color to green to indicate ongoing communication
					_ui_set_panel_color(ui_Panel1, 2);
					_ui_set_panel_color(ui_Panel2, 2);
					//Change connection status and start timeout timer
					hLoraPingPong.pingpong_status.flags.connectionActive = 1;
					hLoraPingPong.timeout = SYS_TICK();
					rssi = 0;
				}
				else if(PINGPONG_RX_TIMEOUT == messageId && hLoraPingPong.pingpong_status.flags.connectionActive)
				{
					_ui_slider_set_property(ui_Slider1, _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM, 100 - rssi);
					_ui_set_panel_color(ui_Panel1, 1);
					_ui_set_panel_color(ui_Panel2, 1);
				}

				else if (PINGPONG_RECEIVED == messageId || PINGPONG_SENT == messageId)
				{
	//				ESP_LOGI(MAIN, "PING PONG");
					pingpongId = lora_pingpongDetect (logBuffer, messageId);
					if(PINGPONG_PING == pingpongId)
					{
	//					ESP_LOGI(MAIN, "PING Id: %d",messageId);
						++hLoraPingPong.pingCounter;
						sprintf(panelString, "%d", hLoraPingPong.pingCounter);
						lv_textarea_set_text(ui_TextArea1, panelString);

					}
					else if(PINGPONG_PONG == pingpongId)
					{
	//					ESP_LOGI(MAIN, "PONG Id: %d",messageId);
						++hLoraPingPong.pongCounter;
						sprintf(panelString, "%d", hLoraPingPong.pongCounter);
						lv_textarea_set_text(ui_TextArea2, panelString);
					}
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
				_ui_set_panel_color(ui_Panel1, 0);
				_ui_set_panel_color(ui_Panel2, 0);
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

			if(hLoraPingPong.pingpong_status.flags.connectionActive)
			{
				char timeString[20] = {0};
				sprintf(timeString,"%02d:%02d", hLoraPingPong.minutes, hLoraPingPong.seconds);
				lora_timeHandler(SYS_TICK());
				lv_label_set_text(ui_Label3, timeString);
			}
			else
			{
				lv_label_set_text(ui_Label3, "00:00");
			}

		}

//		vTaskDelay(50/portTICK_PERIOD_MS);
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
