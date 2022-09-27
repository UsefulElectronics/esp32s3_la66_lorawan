
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  gpio_ui.c
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Sep 27, 2022
 * @brief   		:
 *
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "gpio_ui.h"

/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
SemaphoreHandle_t button_sem 	  		= NULL;
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
void gpioIntConfig(uint8_t gpioNum)
{
	gpio_config_t Button_Config;
	Button_Config.intr_type = GPIO_INTR_NEGEDGE;
	Button_Config.mode = GPIO_MODE_INPUT;
	Button_Config.pin_bit_mask = 1 << gpioNum;
	Button_Config.pull_down_en = GPIO_PULLDOWN_DISABLE;
	Button_Config.pull_up_en = GPIO_PULLUP_ENABLE;
	gpio_config(&Button_Config);
	gpio_install_isr_service(ESP_INTR_FLAG_LEVEL2);
	gpio_isr_handler_add(gpioNum, gpioIsrHandler, (void*) gpioNum);

}

void gpioIsrHandler(void *arg)								  //Falling edge interrupt used to turn on reception Triggering timer once start bit is detected
{
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	uint8_t gpio_idx = (uint8_t) arg;
	uint8_t Interrupt_Enable = DISABLE;
	int16_t Debounce_Counter = 1000;
	uint32_t gpio_intr_status = READ_PERI_REG(GPIO_STATUS_REG);   //read status to get interrupt status for GPIO0-31
	uint32_t gpio_intr_status_h = READ_PERI_REG(GPIO_STATUS1_REG);//read status1 to get interrupt status for GPIO32-39
	SET_PERI_REG_MASK(GPIO_STATUS_W1TC_REG, gpio_intr_status);    //Clear intr for gpio0-gpio31
	SET_PERI_REG_MASK(GPIO_STATUS1_W1TC_REG, gpio_intr_status_h); //Clear intr for gpio32-39

//	ESP_LOGW(TAG, "Button pressed");
	while((Debounce_Counter >= 0) && (Debounce_Counter <= 4000))  //Setting software capacitor to detect
	{															  //To find out if the intrrupt is real or not
		if(gpio_get_level(gpio_idx) == GPIO_SET)				  //Debounce the pin responsible for interrupt
		{
			Debounce_Counter--;
		}
		else
		{
			Debounce_Counter++;
		}

	}
	if(gpio_idx == BTN_EX_IN)
	{
		Debounce_Counter = 4000;
	}
	if(Debounce_Counter >= 4000 )								  //Debounce counter has reached threshold
	{
		Debounce_Counter = 1000;
		ButtonIsrGPIO = gpio_idx;								  //Pass the pin responsible for interrupt
		xSemaphoreGiveFromISR(Button_TXsem, &xHigherPriorityTaskWoken);
        if(xHigherPriorityTaskWoken)
        {
            portYIELD_FROM_ISR();
        }
	}

//	if(Interrupt_Enable == ENABLE)
//	{
//		Interrupt_Enable = DISABLE;
//		switch (gpio_idx)											  //Determine the interrupt source
//		{
//			case BTN_UP:
//				gpio_set_level(LED_DW, GPIO_RESET);
//				break;
//			case BTN_DW:
//				gpio_set_level(LED_DW, GPIO_SET);
//				break;
//			case BTN_OK:
//				gpio_set_level(LED_DW, LED_Toggle);
//				LED_Toggle ^= 1;
//				break;
//			default:
//				break;
//		}
//	}



}

/**************************  Useful Electronics  ****************END OF FILE***/
