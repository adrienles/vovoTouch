// Intentionally left minimal.
// RangeInputTile is a class template. Its method definitions live in the header
// so that all translation units that instantiate it can see the definitions.
#include "RangeInputTile.hpp"

void RangeInputTile::increment()
{
    if (position + 1 >= range)
    {
        position = 0;
    }
    else
    {
        position++;
    }

    lv_image_set_src(imageIndicators, rangePositionDots[position]);
}

void RangeInputTile::decrement()
{
    if (position <= 0)
    {
        position = range - 1;
    }
    else
    {
        position--;
    }

    lv_image_set_src(imageIndicators, rangePositionDots[position]);
}

void RangeInputTile::setupStyle()
{
    // Tile style
    lv_obj_set_style_pad_all(tile, GAP_MD, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(tile, GAP_MD, LV_PART_MAIN);

    // Tile layout
    lv_obj_set_layout(tile, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(tile, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_grow(tile, 1);
}

void RangeInputTile::createIconLabel(const lv_image_dsc_t *iconSrc, const char *title)
{
    iconLabel = lv_obj_create(tile);
    lv_obj_remove_style_all(iconLabel);

    lv_obj_set_layout(iconLabel, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(iconLabel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(iconLabel, LV_FLEX_ALIGN_SPACE_BETWEEN,
                          LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_size(iconLabel, LV_SIZE_CONTENT, lv_pct(100));

    icon = lv_image_create(iconLabel);
    lv_image_set_src(icon, iconSrc);

    imageIndicators = lv_image_create(icon);
    lv_image_set_src(imageIndicators, rangePositionDots[position]);

    lv_obj_align(icon, LV_ALIGN_CENTER, 0, 0);

    label = lv_label_create(iconLabel);
    lv_label_set_text(label, title);
    lv_obj_set_style_text_color(label, COLOR_TEXT, LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &sf_comp_round_semibold_24, LV_PART_MAIN);
}

void RangeInputTile::createRangeButtons()
{
    buttonContainer = lv_obj_create(tile);
    lv_obj_remove_style_all(buttonContainer);

    // Range Buttons style
    lv_obj_set_style_pad_gap(buttonContainer, GAP_LG, LV_PART_MAIN);

    lv_obj_set_layout(buttonContainer, LV_LAYOUT_FLEX);

    lv_obj_set_flex_flow(buttonContainer, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(buttonContainer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_CENTER);

    lv_obj_set_size(buttonContainer, LV_SIZE_CONTENT, lv_pct(100));

    // Buttons
    plusBtn = new RoundButton(buttonContainer, directionIcons[0]);
    plusBtn->addCallback(plusBtnCb, this);

    minusBtn = new RoundButton(buttonContainer, directionIcons[1]);
    minusBtn->addCallback(minusBtnCb, this);
}

void RangeInputTile::plusBtnCb(lv_event_t *e)
{
    RangeInputTile *cbOrigin = static_cast<RangeInputTile *>(lv_event_get_user_data(e));
    cbOrigin->increment();
}

void RangeInputTile::minusBtnCb(lv_event_t *e)
{
    RangeInputTile *cbOrigin = static_cast<RangeInputTile *>(lv_event_get_user_data(e));
    cbOrigin->decrement();
}
