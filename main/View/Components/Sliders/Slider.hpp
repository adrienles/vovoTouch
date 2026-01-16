#pragma once

#include <lvgl.h>

class Slider
{
public:
    explicit Slider(lv_obj_t *parent, uint8_t numIncrements)
    {
        slider = lv_slider_create(parent);
        lv_slider_set_range(slider, 0, numIncrements-1);

        setupStyle();
    }

private:
    void setupStyle();

    static void stateChanged(lv_event_t* e);

    lv_obj_t *slider;
};
