#include "Page.hpp"

#include "../Config/UIConstants.hpp"

Page::Page(lv_obj_t* parent) {
    page = lv_obj_create(parent);

    // Page style
    lv_obj_remove_style_all(page);

    lv_obj_set_style_radius(page, GAP_LG, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(page, GAP_SM, LV_PART_MAIN);
    lv_obj_set_style_clip_corner(page, true, LV_PART_MAIN);

    // Page layout
    lv_obj_set_layout(page, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(page, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(page, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_grow(page, 1);
}

Page::~Page() {
    if (page != nullptr) {
        lv_obj_delete(page);
        page = nullptr;
    }
}
