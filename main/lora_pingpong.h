
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

/* ENUMORATIONS --------------------------------------------------------------*/
typedef enum
{
	SENT,
	RECEIVED,
	RSSI,
	SNR,
	RX_TIMEOUT

}pingpongMsgId_e;
/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef struct
{

};
/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void lora_packetDetect		(uint8_t* buffer);
void lora_connectionTimeout	(uint8_t* buffer);
void lora_getParameter		(uint8_t* buffer);
void lora_getSentMsg		(uint8_t* buffer);
void lora_getReceivedMsg	(uint8_t* buffer);

#endif /* MAIN_LORA_PINGPONG_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
