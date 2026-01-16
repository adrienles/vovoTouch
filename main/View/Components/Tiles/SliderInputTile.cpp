#include "SliderInputTile.hpp"

#include "../Sliders/Slider.hpp"

LV_FONT_DECLARE(sf_comp_round_semibold_24)

void SliderInputTile::setupStyle() {
    // Tile layout
    lv_obj_set_style_pad_all(tile, GAP_MD, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(tile, GAP_MD, LV_PART_MAIN);

    lv_obj_set_layout(tile, LV_LAYOUT_FLEX);

    lv_obj_set_flex_flow(tile, LV_FLEX_FLOW_COLUMN);

    lv_obj_set_size(tile, lv_pct(100), LV_SIZE_CONTENT);
}

void SliderInputTile::createSlider() {
    Slider* slider = new Slider(tile, 4);
}

void SliderInputTile::createDescription(const char* title, const lv_image_dsc_t* iconSrc) {
    lv_obj_t* descriptionContainer = lv_obj_create(tile);
    lv_obj_remove_style_all(descriptionContainer);

    // Description layout
    lv_obj_set_layout(descriptionContainer, LV_LAYOUT_FLEX);

    lv_obj_set_flex_flow(descriptionContainer, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(descriptionContainer, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END);

    lv_obj_set_size(descriptionContainer, lv_pct(100), LV_SIZE_CONTENT);

    // Title label
    lv_obj_t* titleLabel = lv_label_create(descriptionContainer);
    lv_label_set_text(titleLabel, title);
    lv_obj_set_style_text_font(titleLabel, &sf_comp_round_semibold_24, LV_PART_MAIN);
    lv_obj_set_style_text_color(titleLabel, COLOR_TEXT, LV_PART_MAIN);

    // Icon
    lv_obj_t* icon = lv_image_create(descriptionContainer);
    lv_image_set_src(icon, iconSrc);
}
