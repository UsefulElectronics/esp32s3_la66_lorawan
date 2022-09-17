
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  lora_pingpong.h
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Sep 14, 2022
 * @brief   		:
 *
 ******************************************************************************/

#ifndef MAIN_LORA_PINGPONG_H_
#define MAIN_LORA_PINGPONG_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
/* MACROS --------------------------------------------------------------------*/
#define LORA_TIMEOUT		10000
/* ENUMORATIONS --------------------------------------------------------------*/
typedef enum
{
	PINGPONG_SENT,
	PINGPONG_RECEIVED,
	PINGPONG_RSSI,
	PINGPONG_SNR,
	PINGPONG_RX_TIMEOUT,
	PINGPONG_MAX
}pingpongMsgId_e;
/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef struct
{
	uint32_t timeout;
	union
	{
		uint8_t all;
		struct
		{
			uint8_t reserved			:7,
					connectionActive	:1;
		}flags;
	}pingpong_status;

}hLoraPingpong_t;
/* VARIABLES -----------------------------------------------------------------*/
extern hLoraPingpong_t hLoraPingPong;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/
pingpongMsgId_e lora_packetDetect 		(uint8_t* buffer);
void 			lora_getParameter		(uint8_t* buffer, int8_t* rssiValue);
void 			lora_getSentMsg			(uint8_t* buffer);
void 			lora_getReceivedMsg		(uint8_t* buffer);

#endif /* MAIN_LORA_PINGPONG_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
