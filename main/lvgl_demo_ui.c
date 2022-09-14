
/**
 ******************************************************************************
 * @Channel Link    :  https://www.youtube.com/user/wardzx1
 * @file    		:  lvgl_demo_ui.c
 * @author  		:  Ward Almasarani - Useful Electronics
 * @version 		:  v.1.0
 * @date    		:  Aug 21, 2022
 * @brief   		:
 *
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "lvgl_demo_ui.h"
#include "ui.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/


static lv_style_t style;
static lv_style_t bgStyle;
static lv_style_t titleStyle;

static lv_obj_t *arc[3];
static lv_obj_t *img_logo;
;
static lv_obj_t *dis;
static lv_obj_t *meter;

static lv_obj_t *lebel;
static lv_obj_t *title;

lv_obj_t *tv1;
lv_obj_t *tv2;
lv_obj_t *tv3;

static lv_color_t arc_color[] =
{
    LV_COLOR_MAKE(0xFF, 0x00, 0x28),
    LV_COLOR_MAKE(0x14, 0xFF, 0x00),
    LV_COLOR_MAKE(0xFF, 0xFF, 0xFF),
};

static const char *UI = "example";

char * pLvDebugText = NULL;
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/

void		lvgl_demo_ui(lv_obj_t *scr);
static void bg_timer_cb(lv_timer_t *timer);
static void anim_timer_cb(lv_timer_t *timer);
static void update_text_subscriber_cb(lv_event_t *e);
/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief 	lvgl screen content termination timer callback
 *
 * @param 	timer	:	pointer to timer settings and user parameters
 */
static void bg_timer_cb(lv_timer_t *timer)
{
	static uint8_t flipPage = 1;


	lv_obj_set_tile_id(dis, 0, flipPage, LV_ANIM_ON);

//	flipPage ^= 1;


}

void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}

/**
 * @brief 	lvgl screen animation timer callback
 *
 * @param 	timer	:	pointer to timer settings and user parameters
 */
static void anim_timer_cb(lv_timer_t *timer)
{
    my_timer_context_t *timer_ctx = (my_timer_context_t *) timer->user_data;
    int count = timer_ctx->count_val;
    lv_obj_t *scr = timer_ctx->scr;

    // Play arc animation
    if (count < 90)
    {
        lv_coord_t arc_start = count > 0 ? (1 - cosf(count / 180.0f * PI)) * 270 : 0;
        lv_coord_t arc_len = (sinf(count / 180.0f * PI) + 1) * 135;

        for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++) {
            lv_arc_set_bg_angles(arc[i], arc_start, arc_len);
            lv_arc_set_rotation(arc[i], (count + 120 * (i + 1)) % 360);
        }
    }

    // Delete arcs when animation finished
    if (count == 90)
    {
        for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++)
        {
            lv_obj_del(arc[i]);
        }

        // Create new image and make it transparent

        title = lv_label_create(scr);
        lv_obj_add_style(title, &titleStyle, 0);
        lv_label_set_text(title, "USEFUL ELECTRONICS");
        lv_obj_set_style_text_opa(title, 0, 0);
    }

    // Move images when arc animation finished
    if ((count >= 100) && (count <= 180))
    {
        lv_coord_t offset = (sinf((count - 140) * 2.25f / 90.0f) + 1) * 20.0f;
        lv_obj_align(img_logo, LV_ALIGN_CENTER, 0, -offset);
        lv_obj_align(title, LV_ALIGN_CENTER, 0, 1 * offset);
        //as offset changes increase text opacity
        lv_obj_set_style_text_opa(title, offset / 40.0f * 255, 0);
    }



    // Delete timer when all animation finished
    if ((count += 5) == 220)
    {
        lv_timer_del(timer);
        //use full color with the title text
        lv_obj_set_style_text_opa(title, 255, 0);

        //Create rolling text
        lebel = lv_label_create(scr);
        lv_obj_add_style(lebel, &style, 0);
        lv_label_set_long_mode(lebel, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
        //To let scroll feature work properly, the text size must be larger than the assigned size.
        lv_obj_set_width(lebel, 150);
        lv_label_set_text(lebel, "SUBSCRIBE");
        lv_obj_align(lebel, LV_ALIGN_CENTER, 0, 65);

        //create page flip timer
        lv_timer_create(bg_timer_cb, 5000, NULL);
    }
    else
    {
        timer_ctx->count_val = count;
    }
}
/**
 * @brief 	This call back takes place whenever
 *
 * @param e
 */
static void update_text_subscriber_cb(lv_event_t *e)
{
  lv_obj_t *label = lv_event_get_target(e);

  lv_msg_t *m = lv_event_get_msg(e);

  const char *v = (const char *)lv_msg_get_payload(m);

  lv_label_set_text(label, v);

}

/**
 * @brief Start creating user interface elements
 *
 * @param scr	:	pointer to the Background object
 */
void lvgl_demo_ui(lv_obj_t *scr)
{

	//Initialize 3 tiles that act as pages
	dis = lv_tileview_create(scr);
	lv_obj_align(dis, LV_ALIGN_TOP_RIGHT, 0, 0);
	tv1 = lv_tileview_add_tile(dis, 0, 0, LV_DIR_HOR);
	tv2 = lv_tileview_add_tile(dis, 0, 1, LV_DIR_HOR);
	tv3 = lv_tileview_add_tile(dis, 0, 2, LV_DIR_HOR);
	//Page 1
    // Create image useful electronics logo and put it in the center
	img_logo = lv_img_create(tv1);
    lv_img_set_src(img_logo, &ue_logo);
    lv_obj_center(img_logo);
    //create style to manipulate objects characteristics implicitly
    lv_style_init(&style);
    lv_style_init(&bgStyle);
    lv_style_init(&titleStyle);

    //lv_color_hex(0xblue 0xred 0xgreen) //0xF8FCF8 is white
    lv_color_t textColor16 = lv_color_hex(0x14FF00);	//0x014FF00	is purple
    lv_style_set_text_color(&style,textColor16);
    lv_style_set_text_font(&style,  &lv_font_montserrat_28);
    //Change background color
    textColor16 = lv_color_hex(0x000000);
    lv_obj_add_style(dis, &bgStyle, 0);
    lv_style_set_bg_color(&bgStyle, textColor16);
    //Change title text style
    textColor16 = lv_color_hex(0xFF0028);				//0xF8FCF8 is white //0xFF0028 is cyan
    lv_style_set_text_color(&titleStyle,textColor16);
    lv_style_set_text_font(&titleStyle,  &lv_font_montserrat_26);

    //Page 2
    lv_obj_t *debug_label = lv_label_create(tv2);

//    lv_label_set_text(debug_label, pLvDebugText);
    lv_obj_align(debug_label, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_add_event_cb(debug_label, update_text_subscriber_cb, LV_EVENT_MSG_RECEIVED, NULL);
    lv_label_set_text(debug_label, "0%");
    lv_msg_subscribe_obj(MSG_NEW_LOG, debug_label, (void *)"%s");
    //Page 3
    ui_init(tv3);




    // Create arcs
    for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++)
    {
        arc[i] = lv_arc_create(tv1);

        // Set arc caption
        lv_obj_set_size(arc[i], 220 - 30 * i, 220 - 30 * i);
        lv_arc_set_bg_angles(arc[i], 120 * i, 10 + 120 * i);
        lv_arc_set_value(arc[i], 0);

        // Set arc style
        lv_obj_remove_style(arc[i], NULL, LV_PART_KNOB);
        lv_obj_set_style_arc_width(arc[i], 10, 0);
        lv_obj_set_style_arc_color(arc[i], arc_color[i], 0);

        // Make arc center
        lv_obj_center(arc[i]);
    }

    // Create timer for animation
    static my_timer_context_t my_tim_ctx =
    {
        .count_val = -90,
    };
    my_tim_ctx.scr = tv1;



    ESP_LOGI(UI, "Start LV timer");
    lv_timer_create(anim_timer_cb, 20, &my_tim_ctx);


}


/**************************  Useful Electronics  ****************END OF FILE***/





