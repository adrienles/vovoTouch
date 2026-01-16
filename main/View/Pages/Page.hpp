#pragma once

#include <lvgl.h>

class Page
{
protected:
    explicit Page(lv_obj_t *parent);
    ~Page();

    lv_obj_t* page;
};
