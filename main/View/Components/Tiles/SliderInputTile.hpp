#pragma once

#include <lvgl.h>
#include "Tile.hpp"

class SliderInputTile : public Tile
{
public:
    explicit SliderInputTile(lv_obj_t *parent, const lv_image_dsc_t *iconSrc, const char *title, const uint8_t numPositions = 4) : Tile(parent), numPositions(numPositions)
    {
        setupStyle();

        createSlider();
        createDescription(title, iconSrc);
    }

private:
    void setupStyle();

    void createSlider();
    void createDescription(const char* title, const lv_image_dsc_t* iconSrc);

    uint8_t numPositions = 0;
};
