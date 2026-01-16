#pragma once

#include <lvgl.h>
#include "Tile.hpp"

class ClockTile : public Tile {
    public:
        explicit ClockTile(lv_obj_t* parent) : Tile(parent) {
            setupStyle();

            setupClock();
            setupDate();
        }
    private:
        void setupStyle();
        void setupClock();
        void setupDate();

        lv_obj_t* clock;
        lv_obj_t* date;
};
