#include "ClockTile.hpp"

LV_FONT_DECLARE(sf_comp_round_semibold_128)
LV_FONT_DECLARE(sf_comp_round_semibold_36)

void ClockTile::setupStyle() {
    lv_obj_set_size(tile, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_grow(tile, 1);
    lv_obj_set_flex_flow(tile, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(tile, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_hor(tile, GAP_MD, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(tile, GAP_MD, LV_PART_MAIN);
    lv_obj_set_style_pad_top(tile, GAP_LG, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(tile, GAP_MD, LV_PART_MAIN);
}

void ClockTile::setupClock() {
    lv_obj_t* clockContainer = lv_obj_create(tile);
    lv_obj_remove_style_all(clockContainer);

    lv_obj_set_size(clockContainer, lv_pct(100), LV_SIZE_CONTENT);

    clock = lv_label_create(clockContainer);

    lv_label_set_text(clock, "17:38");
    lv_obj_set_style_text_font(clock, &sf_comp_round_semibold_128, LV_PART_MAIN);
    lv_obj_set_style_text_color(clock, COLOR_TEXT, LV_PART_MAIN);
    lv_obj_center(clock);
}

void ClockTile::setupDate() {
    date = lv_label_create(tile);

    lv_label_set_text(date, "Vendredi, 26 septembre 2025");
    lv_obj_set_style_text_font(date, &sf_comp_round_semibold_36, LV_PART_MAIN);
    lv_obj_set_width(date, lv_pct(100));
    lv_obj_set_style_text_color(date, COLOR_TEXT, LV_PART_MAIN);
}
