#include "WeatherTile.hpp"

#include "../../Config/UIPalette.hpp"

LV_FONT_DECLARE(sf_comp_round_semibold_24);
LV_FONT_DECLARE(sf_comp_round_semibold_48);

void WeatherTile::setupStyle() {
    lv_obj_set_flex_flow(tile, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(tile, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    lv_obj_set_style_pad_all(tile, GAP_MD, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(tile, GAP_MD, LV_PART_MAIN);

    lv_obj_set_size(tile, lv_pct(100), LV_SIZE_CONTENT);
}

void WeatherTile::createWeatherUI() {
    temperatureLabel = lv_label_create(tile);
    lv_label_set_text(temperatureLabel, "27ºC");
    lv_obj_set_style_text_font(temperatureLabel, &sf_comp_round_semibold_48, LV_PART_MAIN);
    lv_obj_set_style_text_color(temperatureLabel, COLOR_TEXT, LV_PART_MAIN);

    cityLabel = lv_label_create(tile);
    lv_label_set_text(cityLabel, "Montréal");
    lv_obj_set_style_text_font(cityLabel, &sf_comp_round_semibold_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(cityLabel, COLOR_TEXT, LV_PART_MAIN);
}
