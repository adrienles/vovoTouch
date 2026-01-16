#include "Home.hpp"

LV_IMAGE_DECLARE(ToiletSeatTemp);

void Home::setupStyle() {
    lv_obj_set_layout(page, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(page, LV_FLEX_FLOW_ROW);
}

void Home::createLeftContainer() {
    lv_obj_t* leftContainer = lv_obj_create(page);
    lv_obj_remove_style_all(leftContainer);

    lv_obj_set_size(leftContainer, lv_pct(100), lv_pct(100));
    lv_obj_set_style_pad_gap(leftContainer, GAP_SM, LV_PART_MAIN);
    lv_obj_set_flex_flow(leftContainer, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_grow(leftContainer, 2);

    clockTile = new ClockTile(leftContainer);

    seatTemperatureTile = new SliderInputTile(leftContainer, &ToiletSeatTemp, lv_tr("seatTempLbl"), 4);
}

void Home::createRightContainer() {
    lv_obj_t* rightContainer = lv_obj_create(page);
    lv_obj_remove_style_all(rightContainer);

    lv_obj_set_size(rightContainer, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_grow(rightContainer, 1);

    weatherTile = new WeatherTile(rightContainer);
}
