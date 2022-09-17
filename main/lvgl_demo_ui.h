
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  lvgl_demo_ui.h
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Aug 21, 2022
 * @brief   		:
 *
 ******************************************************************************/

#ifndef MAIN_LVGL_DEMO_UI_H_
#define MAIN_LVGL_DEMO_UI_H_


/* INCLUDES ------------------------------------------------------------------*/
#include <math.h>
#include "lvgl.h"
#include "esp_log.h"

#include "ui.h"
#include "ui_helpers.h"
/* MACROS --------------------------------------------------------------------*/
#ifndef PI
#define PI  (3.14159f)
#endif

LV_IMG_DECLARE(ue_logo)

#define MSG_NEW_LOG   		1

/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/
typedef struct
{
    lv_obj_t *scr;
    int count_val;
} my_timer_context_t;
/* VARIABLES -----------------------------------------------------------------*/

/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void lvgl_demo_ui	(lv_obj_t *scr);
void changePage		(void);
//void lvgl_system_logger(char *textPointer);
#endif /* MAIN_LVGL_DEMO_UI_H_ */

/**************************  Useful Electronics  ****************END OF FILE***/
