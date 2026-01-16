#pragma once

#include "../Buttons/RoundButton.hpp"
#include "Tile.hpp"
// #include "misc/lv_area.h"
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_style.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/core/lv_obj_tree.h>
#include <src/layouts/flex/lv_flex.h>
#include <src/layouts/lv_layout.h>
#include <src/misc/lv_types.h>
#include <src/widgets/label/lv_label.h>

LV_FONT_DECLARE(sf_comp_round_semibold_24)

class RangeInputTile : public Tile {
    public:
        explicit RangeInputTile(lv_obj_t* parent, const lv_image_dsc_t* iconSrc, const lv_image_dsc_t* directionIconSrc[],
            const lv_image_dsc_t* indicatorImageSrc[],
            const char* title, const uint8_t range)
            : Tile(parent)
            , directionIcons(directionIconSrc)
            , rangePositionDots(indicatorImageSrc)
            , range(range) {
            setupStyle();

            createIconLabel(iconSrc, title);
            createRangeButtons();
        }

        ~RangeInputTile() = default;

        void increment();
        void decrement();

    private:
        void setupStyle();

        void createIconLabel(const lv_image_dsc_t* iconSrc, const char* title);
        void createRangeButtons();

        static void plusBtnCb(lv_event_t* e);
        static void minusBtnCb(lv_event_t* e);

        const lv_img_dsc_t** directionIcons;

        const lv_img_dsc_t** rangePositionDots;
        uint8_t position = 0;
        uint8_t range;

        lv_obj_t* iconLabel;
        lv_obj_t* icon;
        lv_obj_t* imageIndicators;
        lv_obj_t* label;

        lv_obj_t* buttonContainer;
        RoundButton* plusBtn;
        RoundButton* minusBtn;
};
