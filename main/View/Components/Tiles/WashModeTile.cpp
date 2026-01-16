// #include "WashModeTile.hpp"



// void WashModeTile::setupStyle()
// {
//     // Tile layout
//     lv_obj_set_size(tile, lv_pct(100), LV_SIZE_CONTENT);

//     lv_obj_set_style_pad_all(tile, GAP_SM, LV_PART_MAIN);
//     lv_obj_set_style_pad_gap(tile, GAP_SM, LV_PART_MAIN);

//     lv_obj_set_flex_flow(tile, LV_FLEX_FLOW_ROW);
//     lv_obj_set_flex_grow(tile, 1);
// }

// void WashModeTile::createDescriptionContainer(const lv_image_dsc_t *iconSrc, const char *title)
// {
//     lv_obj_t *descriptionContainer = lv_obj_create(tile);
//     lv_obj_remove_style_all(descriptionContainer);

//     // Description container layout

//     lv_obj_set_height(descriptionContainer, lv_pct(100));
//     lv_obj_set_style_pad_ver(descriptionContainer, GAP_SM, LV_PART_MAIN);
//     lv_obj_set_style_pad_left(descriptionContainer, GAP_SM, LV_PART_MAIN);

//     lv_obj_set_layout(descriptionContainer, LV_LAYOUT_FLEX);

//     lv_obj_set_flex_flow(descriptionContainer, LV_FLEX_FLOW_COLUMN);
//     lv_obj_set_flex_align(descriptionContainer, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
//     lv_obj_set_flex_grow(descriptionContainer, 2);

//     // Icon container
//     lv_obj_t *iconContainer = lv_obj_create(descriptionContainer);
//     lv_obj_remove_style_all(iconContainer);

//     lv_obj_set_style_pad_left(iconContainer, GAP_SM, LV_PART_MAIN);

//     // Icon container padding
//     lv_obj_set_size(iconContainer, lv_pct(100), LV_SIZE_CONTENT);

//     // Icon
//     lv_obj_t *icon = lv_image_create(iconContainer);
//     lv_image_set_src(icon, iconSrc);

//     // Description
//     lv_obj_t *descriptionLabel = lv_label_create(descriptionContainer);
//     lv_label_set_text(descriptionLabel, title);
//     lv_obj_set_style_text_color(descriptionLabel, COLOR_TEXT, LV_PART_MAIN);
//     lv_obj_set_style_text_font(descriptionLabel, &sf_comp_round_semibold_24, LV_PART_MAIN);
// }

// void WashModeTile::createButtonContainer(const bool hasTurboMode)
// {
//     lv_obj_t *buttonContainer = lv_obj_create(tile);
//     lv_obj_remove_style_all(buttonContainer);

//     // Button container layout
//     lv_obj_set_size(buttonContainer, lv_pct(100), lv_pct(100));

//     lv_obj_set_layout(buttonContainer, LV_LAYOUT_FLEX);
//     lv_obj_set_flex_grow(buttonContainer, 5);

//     lv_obj_set_style_bg_color(buttonContainer, LV_COLOR_MAKE(37, 37, 37), LV_PART_MAIN);
//     lv_obj_set_style_bg_opa(buttonContainer, LV_OPA_100, LV_PART_MAIN);
//     lv_obj_set_style_radius(buttonContainer, GAP_SM, LV_PART_MAIN);

//     lv_obj_set_style_pad_all(buttonContainer, 6, LV_PART_MAIN);
//     lv_obj_set_style_pad_gap(buttonContainer, 6, LV_PART_MAIN);

//     BidetButton* continuousBtn = new BidetButton(buttonContainer, lv_tr("continuousLbl"));

//     lv_obj_t *extraModesContainer = lv_obj_create(buttonContainer);
//     lv_obj_remove_style_all(extraModesContainer);

//     lv_obj_set_size(extraModesContainer, lv_pct(100), lv_pct(100));

//     lv_obj_set_layout(extraModesContainer, LV_LAYOUT_FLEX);
//     lv_obj_set_flex_flow(extraModesContainer, LV_FLEX_FLOW_COLUMN);
//     lv_obj_set_flex_grow(extraModesContainer, 1);
//     lv_obj_set_style_pad_gap(extraModesContainer, 6, LV_PART_MAIN);

//     BidetButton *rhythmBtn = new BidetButton(extraModesContainer, lv_tr("rhythmLbl"));

//     if (hasTurboMode) {
//         BidetButton *turboBtn = new BidetButton(extraModesContainer, lv_tr("turboLbl"));
//     }
//     // // Buttons
//     // lv_obj_t* tempButtons = lv_obj_create(buttonContainer);
//     // lv_obj_remove_style_all(tempButtons);
//     // lv_obj_set_size(tempButtons, lv_pct(100), lv_pct(100));

//     // lv_obj_set_flex_grow(tempButtons, 1);
// }
