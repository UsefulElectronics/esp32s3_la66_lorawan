// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: LA66_Interface

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////

lv_obj_t * ui_Slider1;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Label6;
lv_obj_t * ui_Panel1;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(lv_obj_t *ui_Screen1)
{
//    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label5 = lv_label_create(ui_Screen1);
     lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
     lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
     lv_obj_set_x(ui_Label5, -117);
     lv_obj_set_y(ui_Label5, -30);
     lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
     lv_label_set_text(ui_Label5, "RSSI Level");

     ui_Label6 = lv_label_create(ui_Screen1);
     lv_obj_set_width(ui_Label6, lv_pct(53));
     lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
     lv_obj_set_x(ui_Label6, -71);
     lv_obj_set_y(ui_Label6, -60);
     lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
     lv_label_set_text(ui_Label6, "Connection Status");

     ui_Panel1 = lv_obj_create(ui_Screen1);
     lv_obj_set_width(ui_Panel1, 20);
     lv_obj_set_height(ui_Panel1, 21);
     lv_obj_set_x(ui_Panel1, 124);
     lv_obj_set_y(ui_Panel1, -60);
     lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
     lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
     lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x595959), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

     ui_Slider1 = lv_slider_create(ui_Screen1);
     lv_slider_set_value(ui_Slider1, 50, LV_ANIM_OFF);
     if(lv_slider_get_mode(ui_Slider1) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Slider1, 0, LV_ANIM_OFF);
     lv_obj_set_width(ui_Slider1, 97);
     lv_obj_set_height(ui_Slider1, 10);
     lv_obj_set_x(ui_Slider1, 96);
     lv_obj_set_y(ui_Slider1, -30);
     lv_obj_set_align(ui_Slider1, LV_ALIGN_CENTER);
     lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
     lv_obj_set_style_bg_opa(ui_Slider1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

     lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0xFF0028), LV_PART_INDICATOR | LV_STATE_DEFAULT);
     lv_obj_set_style_bg_opa(ui_Slider1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

     lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0xFF00028), LV_PART_KNOB | LV_STATE_DEFAULT);
     lv_obj_set_style_bg_opa(ui_Slider1, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
     lv_obj_set_style_pad_left(ui_Slider1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
     lv_obj_set_style_pad_right(ui_Slider1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
     lv_obj_set_style_pad_top(ui_Slider1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
     lv_obj_set_style_pad_bottom(ui_Slider1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
     lv_obj_set_style_pad_row(ui_Slider1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
     lv_obj_set_style_pad_column(ui_Slider1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
}

void ui_init(lv_obj_t *ui_Screen1)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init(ui_Screen1);
//    lv_disp_load_scr(ui_Screen1);
}
