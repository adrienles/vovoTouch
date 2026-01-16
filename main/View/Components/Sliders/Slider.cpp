#include "Slider.hpp"

#include "../../Config/UIPalette.hpp"
#include <iostream>
// #include "misc/lv_color.h"
// #include "core/lv_obj_style.h"
// #include "core/lv_obj_style_gen.h"
// #include "misc/lv_color.h"

void Slider::setupStyle() {
    // Slider style
    // lv_obj_remove_style_all(slider);
    lv_obj_set_size(slider, lv_pct(100), 36);

    // Slider bar style
    // lv_obj_set_style_size(slider, lv_pct(100), 28, LV_PART_MAIN);
    // lv_obj_set_style_bg_grad
    // static lv_grad_dsc_t gradientBackground;
    // static lv_color_t gradientColors[] = {COLOR_SLIDER_BLUE, COLOR_SLIDER_RED};
    // lv_grad_init_stops(&gradientBackground, gradientColors, NULL, NULL, 2);
    // lv_obj_set_style_bg_opa(slider, LV_OPA_COVER, LV_PART_MAIN);
    // lv_obj_set_style_bg_grad(slider, &gradientBackground, LV_PART_MAIN);
    // lv_obj_set_style_bg_grad_opa(slider, LV_OPA_COVER, LV_PART_MAIN);
    // lv_obj_set_style_pad_all(slider, 4, LV_PART_MAIN);
    lv_obj_set_style_height(slider, 28, LV_PART_MAIN);
    lv_obj_set_style_height(slider, 28, LV_PART_INDICATOR);

    lv_obj_set_style_bg_opa(slider, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_bg_color(slider, COLOR_SLIDER_BLUE, LV_PART_MAIN);
    lv_obj_set_style_bg_grad_color(slider, COLOR_SLIDER_RED, LV_PART_MAIN);
    lv_obj_set_style_bg_grad_dir(slider, LV_GRAD_DIR_HOR, LV_PART_MAIN);

    lv_obj_set_style_bg_color(slider, COLOR_WIDGET_FG, LV_PART_KNOB);
    lv_obj_set_style_pad_all(slider, 4, LV_PART_KNOB);
    // lv_obj_set_style_pad_all(slider, -4, LV_PART_MAIN);
    // lv_obj_set_style_pad_hor(slider, 14, LV_PART_MAIN);

    lv_obj_set_style_bg_opa(slider, LV_OPA_0, LV_PART_INDICATOR);
    lv_obj_set_style_pad_hor(slider, 14, LV_PART_MAIN);
    // lv_obj_set_style_margin_hor(slider, 30, LV_PART_INDICATOR);
    // lv_obj_set_style_margin_hor(slider, -14, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(slider, COLOR_WIDGET_FG, LV_PART_INDICATOR);
    // lv_obj_set_style_margin_left(slider, -14, LV_PART_INDICATOR);
    lv_obj_add_event_cb(slider, stateChanged, LV_EVENT_VALUE_CHANGED, NULL);
}

void Slider::stateChanged(lv_event_t* e) {
    lv_obj_t* origin = lv_event_get_target_obj(e);

    std::cout << lv_slider_get_value(origin) << std::endl;
}
