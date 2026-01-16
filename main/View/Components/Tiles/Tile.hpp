#pragma once

#include "../../Config/UIConstants.hpp"
#include "../../Config/UIPalette.hpp"
#include <lvgl.h>
// #include <src/core/lv_obj.h>
// #include <src/core/lv_obj_pos.h>
// #include <src/core/lv_obj_style_gen.h>
// #include <src/layouts/lv_layout.h>

class Tile
{
protected:
    explicit Tile(lv_obj_t *parent)
    {
        tile = lv_obj_create(parent);

        // Tile style
        lv_obj_remove_style_all(tile);

        lv_obj_set_style_bg_color(tile, COLOR_WIDGET_BG, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, LV_PART_MAIN);
        lv_obj_set_style_radius(tile, GAP_MD, LV_PART_MAIN);
        lv_obj_set_layout(tile, LV_LAYOUT_FLEX);
        lv_obj_set_size(tile, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    }

    ~Tile()
    {
        if (tile != nullptr)
        {
            lv_obj_delete(tile);
            tile = nullptr;
        }
    }

    lv_obj_t *tile;
};
