#pragma once

#include "Button.hpp"
#include "../../Config/UIConstants.hpp"

LV_FONT_DECLARE(sf_comp_round_bold_64)

class FlushButton : public Button
{
public:
    explicit FlushButton(lv_obj_t *parent, const lv_image_dsc_t *imageSrc, const lv_image_dsc_t *iconSrc, const lv_color_t buttonColor, const bool isRightButton = false)
        : Button(parent, imageSrc, iconSrc, buttonColor)
    {
        lv_obj_set_style_pad_all(button, GAP_MD, LV_PART_MAIN);
        lv_obj_set_flex_flow(button, LV_FLEX_FLOW_COLUMN);
        lv_flex_align_t horizontalAlignment = isRightButton ? LV_FLEX_ALIGN_START : LV_FLEX_ALIGN_END;
        lv_obj_set_flex_align(button, LV_FLEX_ALIGN_START, horizontalAlignment, horizontalAlignment);
        lv_obj_remove_flag(button, LV_OBJ_FLAG_SCROLLABLE);
    }

    explicit FlushButton(lv_obj_t *parent, const lv_image_dsc_t *imageSrc, const char *text, const lv_color_t buttonColor)
        : Button(parent, imageSrc, text, buttonColor)
    {
        lv_obj_set_style_pad_all(button, GAP_MD, LV_PART_MAIN);
        lv_obj_set_flex_flow(button, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(button, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_remove_flag(button, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_text_font(button, &sf_comp_round_bold_64, LV_PART_MAIN);
    }
};
