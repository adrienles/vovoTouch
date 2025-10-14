// Necessary to get the program to compile with C++
#include "esp_lcd_io_i2c.h"

extern "C" {
#include <bsp/display.h>
#include <bsp/esp-bsp.h>
#include <bsp/touch.h>
#include <esp_flash.h>
#include <esp_system.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <lvgl.h>
#include <stdio.h>
}

#include "UI/UI.hpp"

extern "C" void app_main() {
    // Initialize BSP
    bsp_display_start();
    bsp_display_brightness_init();
    bsp_display_backlight_on();
    bsp_display_lock(0);

    // Create UI
    // UI* ui = new UI();

    bsp_display_unlock();
}
