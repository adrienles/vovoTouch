#include "RemoteController.hpp"

void RemoteController::smallFlush() {
    model->smallFlush();
}

void RemoteController::fullFlush() {
    model->fullFlush();
}

void RemoteController::stop() {
    model->stop();
}

void RemoteController::setWashMode(RemoteSettings::WashMode mode) {
    model->setWashMode(mode);
}

void RemoteController::addWashActionInProgressObserver(lv_observer_cb_t callback, void* data) {
    model->addWashActionInProgressObserver(callback, data);
}