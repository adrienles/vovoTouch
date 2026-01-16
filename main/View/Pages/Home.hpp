#pragma once

#include "Page.hpp"
#include "../Components/Tiles/ClockTile.hpp"
#include "../Components/Tiles/SliderInputTile.hpp"
#include "../Components/Tiles/WeatherTile.hpp"

class Home : public Page {
    public:
        explicit Home(lv_obj_t* parent) : Page(parent) {
            createLeftContainer();
            createRightContainer();
        }

        ~Home() = default;

        void reloadSettings();

    private:
        void setupStyle();

        void createLeftContainer();
        void createRightContainer();


        ClockTile* clockTile;
        SliderInputTile* seatTemperatureTile;

        WeatherTile* weatherTile;
};
