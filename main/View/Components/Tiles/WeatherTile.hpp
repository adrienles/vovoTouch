#pragma once

#include "Tile.hpp"

class WeatherTile : public Tile {
    public:
        explicit WeatherTile(lv_obj_t* parent) : Tile(parent) {
            setupStyle();

            createWeatherUI();
        }
    private:
        void setupStyle();

        void createWeatherUI();

        lv_obj_t* cityLabel;
        lv_obj_t* temperatureLabel;
        bool isFahrenheit = false;
};
