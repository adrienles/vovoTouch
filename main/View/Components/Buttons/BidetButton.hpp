#pragma once

#include "ToggleButton.hpp"

LV_FONT_DECLARE(sf_comp_round_semibold_24);

class BidetButton : public ToggleButton {
    public:
        explicit BidetButton(lv_obj_t* parent, const char* text) : ToggleButton(parent, text) {
            lv_obj_set_style_radius(button, 3, LV_PART_MAIN);
            lv_obj_set_size(button, lv_pct(100), lv_pct(100));
            lv_obj_set_flex_grow(button, 1);

            lv_obj_set_style_text_font(button, &sf_comp_round_semibold_24, LV_PART_MAIN);
        }
};
