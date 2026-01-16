#pragma once

// #include "misc/lv_text.h"
// #include "core/lv_obj_style_gen.h"
#include "../../Config/UIPalette.hpp"
#include <lvgl.h>

#ifdef ESP
#include "misc/lv_types.h"
#endif

class Button
{
public:
    explicit Button(lv_obj_t *parent, const lv_image_dsc_t *iconSrc)
        : Button(parent)
    {
        icon = lv_image_create(button);
        lv_image_set_src(icon, iconSrc);

        // Image style
        lv_obj_align(icon, LV_ALIGN_CENTER, 0, 0);
    }

    explicit Button(lv_obj_t *parent, const lv_image_dsc_t *imageSrc, const lv_image_dsc_t *iconSrc, const lv_color_t buttonColor)
        : Button(parent, buttonColor, true)
    {
        lv_imagebutton_set_src(button, LV_IMAGEBUTTON_STATE_RELEASED, NULL, imageSrc, NULL);
        lv_obj_set_style_image_recolor(button, buttonColor, LV_PART_MAIN);
        lv_obj_set_style_image_recolor(button, lv_color_darken(buttonColor, 50), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_image_recolor_opa(button, LV_OPA_100, LV_PART_MAIN);

        icon = lv_image_create(button);
        lv_image_set_src(icon, iconSrc);
    }

    explicit Button(lv_obj_t *parent, const lv_image_dsc_t *imageSrc, const char *text, const lv_color_t buttonColor)
        : Button(parent, buttonColor, true)
    {
        lv_imagebutton_set_src(button, LV_IMAGEBUTTON_STATE_RELEASED, NULL, imageSrc, NULL);
        lv_obj_set_style_image_recolor(button, buttonColor, LV_PART_MAIN);
        lv_obj_set_style_image_recolor(button, lv_color_darken(buttonColor, 50), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_image_recolor_opa(button, LV_OPA_100, LV_PART_MAIN);

        label = lv_label_create(button);
        lv_label_set_text(label, text);

        // Text style
        lv_obj_set_style_text_color(label, COLOR_TEXT, LV_PART_MAIN);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    }

    explicit Button(lv_obj_t *parent, const char *text)
        : Button(parent)
    {
        label = lv_label_create(button);
        lv_label_set_text(label, text);

        // Text style
        lv_obj_set_style_text_color(label, COLOR_TEXT, LV_PART_MAIN);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    }

    ~Button();

    lv_event_dsc_t *addCallback(lv_event_cb_t callback, void *userData);
    void removeCallback(lv_event_cb_t callback);

    lv_obj_t *getObj() { return button; }

protected:
    lv_style_t defaultStyle;

    lv_obj_t *button = nullptr;
    lv_obj_t *icon = nullptr;
    lv_obj_t *label = nullptr;

private:
    Button(lv_obj_t *parent, const lv_color_t buttonColor = COLOR_BTN_BG, const bool isImageButton = false);

    void setupStyle(const lv_color_t buttonColor, const bool isImageButton);
    void setupStyle(const bool isImageButton);
    void setupTransitions();

    lv_style_t pressedDefaultStyle;
    lv_style_t pressedCheckedStyle;
    lv_style_t checkedStyle;
};
