#pragma once

#include "../Models/RemoteModel.hpp"

class RemoteController {
public:
    explicit RemoteController(RemoteModel* model) : model(model) {}

    void smallFlush();
    void fullFlush();
    void stop();

    void setWashMode(RemoteSettings::WashMode mode);

    void addWashActionInProgressObserver(lv_observer_cb_t callback, void* data);

private:
    RemoteModel* model;
};  