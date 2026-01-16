#pragma once

#include "Button.hpp"

#ifdef ESP
    #include "misc/lv_types.h"
#endif

class ToggleButton : public Button {
    protected:
        explicit ToggleButton(lv_obj_t* parent, const lv_image_dsc_t* imageSrc)
            : Button(parent, imageSrc) {
            lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);
        }

        explicit ToggleButton(lv_obj_t* parent, const char* text)
            : Button(parent, text) {
            lv_obj_add_flag(button, LV_OBJ_FLAG_CHECKABLE);
        }

        ~ToggleButton() = default;
};
