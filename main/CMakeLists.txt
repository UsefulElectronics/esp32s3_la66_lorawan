file(GLOB_RECURSE IMAGE_SOURCES images/*.c)


idf_component_register(SRCS "main.c" "uart_config.c" "lvgl_demo_ui.c" "display_config.c" "gpio_ui.c" "ui.c" "lora_pingpong.c" "ui_helpers.c" ${IMAGE_SOURCES}
                       INCLUDE_DIRS ".")
