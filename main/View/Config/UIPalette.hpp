#pragma once

#include <lvgl.h>

#ifdef ESP
    #include "misc/lv_color.h"
#endif

// Background colors
static constexpr lv_color_t COLOR_BG = LV_COLOR_MAKE(16, 16, 16);

// Text color
static constexpr lv_color_t COLOR_TEXT = LV_COLOR_MAKE(255, 255, 255);

// Widget bg/fg colors
static constexpr lv_color_t COLOR_WIDGET_BG = LV_COLOR_MAKE(47, 47, 47);
static constexpr lv_color_t COLOR_WIDGET_FG = LV_COLOR_MAKE(255, 255, 255);

// Button colors
static constexpr lv_color_t COLOR_BTN_BG = LV_COLOR_MAKE(92, 92, 92);
static constexpr lv_color_t COLOR_BTN_PRESSED = LV_COLOR_MAKE(135, 174, 115);
static constexpr lv_color_t COLOR_BTN_SMALL_FLUSH = COLOR_BTN_PRESSED;
static constexpr lv_color_t COLOR_BTN_LARGE_FLUSH = LV_COLOR_MAKE(82, 108, 68);
static constexpr lv_color_t COLOR_BTN_STOP = LV_COLOR_MAKE(226, 68, 68);

// Slider gradient colors
static constexpr lv_color_t COLOR_SLIDER_BLUE = LV_COLOR_MAKE(13, 140, 233);
static constexpr lv_color_t COLOR_SLIDER_RED = LV_COLOR_MAKE(255, 0, 0);

// Flush button colors
static constexpr lv_color_t COLOR_LARGE_FLUSH = LV_COLOR_MAKE(82, 108, 68);
static constexpr lv_color_t COLOR_STOP_FLUSH = LV_COLOR_MAKE(226, 68, 68);
