#pragma once

#include "Page.hpp"
#include <lvgl.h>

class Dry : public Page {
    public:
        explicit Dry(lv_obj_t* parent, RemoteController* remote)
            : Page(parent)
            , remoteController(remote) { }

        ~Dry() = default;

        void reloadSettings();

    private:
        RemoteController* remoteController;
};