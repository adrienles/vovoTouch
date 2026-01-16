#pragma once

#include "Button.hpp"

#ifdef ESP
    #include "misc/lv_types.h"
#endif

LV_FONT_DECLARE(sf_comp_round_bold_48)

class RoundButton : public Button {
    public:
        explicit RoundButton(lv_obj_t* parent, const lv_image_dsc_t *iconSrc)
            : Button(parent, iconSrc) {
            setupStyle();
        }

        ~RoundButton() = default;

    private:
        void setupStyle();
};
