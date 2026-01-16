#pragma once

#include "ToggleButton.hpp"

class QuickAccessButton : public ToggleButton
{
public:
    explicit QuickAccessButton(lv_obj_t *parent, const lv_image_dsc_t *imageSrc)
        : ToggleButton(parent, imageSrc)
    {
        setupStyle();
    }

    ~QuickAccessButton() = default;

private:
    void setupStyle();
};
