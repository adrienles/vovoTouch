#include "esp_lcd_io_i2c.h"

extern "C" {
#include <bsp/display.h>
#include <bsp/esp-bsp.h>
#include <bsp/touch.h>
#include <esp_flash.h>
#include <esp_log.h>
#include <esp_system.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <lvgl.h>
#include <stdio.h>
}

#define LV_USE_RE

#include "View/UI.hpp"
#include "Models/IRTransmitter.hpp"

extern "C" void app_main() {
    // Initialize BSP
    // Increase LVGL task stack to avoid stack canary trips during complex draws
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags = {
#if CONFIG_BSP_LCD_COLOR_FORMAT_RGB888
            .buff_dma = false,
#else
            .buff_dma = true,
#endif
            .buff_spiram = true,
            .sw_rotate = false,
        }
    };

    // Bump LVGL task stack from default (7168) to a safer margin
    cfg.lvgl_port_cfg.task_stack = 24576; // 24 KB

    esp_log_level_set("LVGL", ESP_LOG_DEBUG);

    bsp_display_start_with_config(&cfg);

    for (int i = 0; i < 3; ++i) {
        bsp_display_lock(0);
        lv_obj_t* scr = lv_screen_active();
        lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(scr, lv_color_black(), 0);

        lv_timer_handler();
        bsp_display_unlock();
        vTaskDelay(pdMS_TO_TICKS(16)); // ~1 frame at 60 Hz
    }

    bsp_display_brightness_init();
    bsp_display_backlight_on();
    bsp_display_lock(0);

    // Create UI
    RemoteModel* remoteModel = new RemoteModel();
    RemoteController* remoteController = new RemoteController(remoteModel);

    UI* ui = new UI(remoteController);

    bsp_display_unlock();
}
