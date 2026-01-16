#include "Button.hpp"
// #include "layouts/flex/lv_flex.h"

#ifdef ESP
#include "core/lv_obj_tree.h"
#include "misc/lv_color.h"
#include "widgets/button/lv_button.h"
#endif

#include "../../Config/UIConstants.hpp"
#include "../../Config/UIPalette.hpp"

Button::Button(lv_obj_t *parent, const lv_color_t buttonColor, const bool isImageButton)
{
    if (!isImageButton)
    {
        button = lv_button_create(parent);
    }
    else
    {
        button = lv_imagebutton_create(parent);
    }

    setupStyle(isImageButton);
    lv_obj_remove_style_all(button);

    lv_obj_add_style(button, &defaultStyle, LV_STATE_DEFAULT);
    lv_obj_add_style(button, &pressedDefaultStyle,
                     LV_STATE_DEFAULT | LV_STATE_PRESSED);
    lv_obj_add_style(button, &checkedStyle, LV_STATE_CHECKED);
    lv_obj_add_style(button, &pressedCheckedStyle,
                     LV_STATE_CHECKED | LV_STATE_PRESSED);

    lv_obj_set_layout(button, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(button, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(button, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_CENTER);
};

Button::~Button()
{
    if (button != nullptr)
    {
        lv_obj_delete(button);
        button = nullptr;
        label = nullptr;
        icon = nullptr;
    }
}

lv_event_dsc_t *Button::addCallback(lv_event_cb_t callback, void *userData)
{
    return lv_obj_add_event_cb(button, callback, LV_EVENT_CLICKED, userData);
}

void Button::removeCallback(lv_event_cb_t callback)
{
    lv_obj_remove_event_cb(button, callback);
}

void Button::setupStyle(const bool isImageButton)
{
    setupStyle(COLOR_BTN_BG, isImageButton);
}

void Button::setupStyle(const lv_color_t buttonColor, const bool isImageButton)
{
    lv_style_init(&defaultStyle);
    if (!isImageButton)
    {
        lv_style_set_bg_color(&defaultStyle, buttonColor);
        lv_style_set_bg_opa(&defaultStyle, LV_OPA_COVER);
        lv_style_set_radius(&defaultStyle, GAP_MD);
    }
    else
    {
        lv_obj_set_style_image_recolor(button, buttonColor, LV_PART_MAIN);
        lv_obj_set_style_image_recolor_opa(button, LV_OPA_100, LV_PART_MAIN);
    }

    lv_style_init(&pressedDefaultStyle);
    if (!isImageButton)
    {
        lv_style_set_bg_color(&pressedDefaultStyle,
                              lv_color_lighten(buttonColor, 50));
    }
    else
    {
        lv_obj_set_style_image_recolor(button, lv_color_darken(buttonColor, 50), LV_PART_MAIN | LV_STATE_PRESSED);
    }

    lv_style_init(&pressedCheckedStyle);
    lv_style_set_bg_color(&pressedCheckedStyle,
                          lv_color_darken(COLOR_BTN_PRESSED, 50));

    lv_style_init(&checkedStyle);
    lv_style_set_bg_color(&checkedStyle, COLOR_BTN_PRESSED);

    setupTransitions();
}

void Button::setupTransitions()
{
    static const lv_style_prop_t trans_props[] = {
        LV_STYLE_BG_COLOR, LV_STYLE_IMAGE_RECOLOR, LV_STYLE_IMAGE_RECOLOR_OPA, LV_STYLE_OPA, 0 /* End marker */
    };

    static lv_style_transition_dsc_t transPressed;
    static lv_style_transition_dsc_t transClicked;

    lv_style_transition_dsc_init(&transClicked, trans_props,
                                 lv_anim_path_ease_out, 100, 0, NULL);
    lv_style_transition_dsc_init(&transPressed, trans_props,
                                 lv_anim_path_ease_out, 50, 0, NULL);

    lv_style_set_transition(&defaultStyle, &transClicked);
    lv_style_set_transition(&checkedStyle, &transClicked);
    lv_style_set_transition(&pressedDefaultStyle, &transPressed);
    lv_style_set_transition(&pressedCheckedStyle, &transPressed);
}
