
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  lora_pingpong.c
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Sep 14, 2022
 * @brief   		:
 *
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "lora_pingpong.h"
#include "ctype.h"
#include "esp_log.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
const char pingpongMsg[5][12] =
{
	"Sent",
	"Received",
	"RSSI",
	"SNR",
	"OnRxTimeout"
};
const char *DEBUG_LORA = "LORA";
hLoraPingpong_t hLoraPingPong;
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief 	Find the type of the sent packet
 *
 * @param 	buffer	:	Packet received from LA66 module buffer
 *
 * @return	Found Command ID. If packet is not found then PINGPONG_MAX is returned.
 */
pingpongMsgId_e lora_packetDetect (uint8_t* buffer)
{
	const uint8_t packetOffset 		= 2;
	const uint8_t cahrCompareCount 	= 3;
	pingpongMsgId_e packetId = PINGPONG_SENT;
	for(; packetId < PINGPONG_MAX; ++packetId)
	{
		if(0 == memcmp(buffer + packetOffset, pingpongMsg[packetId], cahrCompareCount))
		{
			break;
		}

	}
	return packetId;
}
/**
 * @brief 	Extract RSSI value from the received command
 *
 * @param 	buffer		:	Packet received from LA66 module buffer
 *
 * @param 	rssiValue	:	RSSI variable address to be copied to
 */
void lora_getParameter		(uint8_t* buffer, int8_t* rssiValue)
{
	const uint8_t packetOffset 		= 9;		//9 + 1
	for(uint8_t i = 0; i < 3; ++i)
	{
		if(isdigit(buffer[packetOffset + i]))
		{
			*rssiValue *= 10;
			*rssiValue += buffer[packetOffset + i] - '0';

		}
		else
		{
			break;
		}
	}
}

//void lora_connectionTimeout	(uint8_t* buffer);
//void lora_getParameter		(uint8_t* buffer, int8_t* rssiValue);
//void lora_getSentMsg		(uint8_t* buffer);
//void lora_getReceivedMsg	(uint8_t* buffer);

/**************************  Useful Electronics  ****************END OF FILE***/
