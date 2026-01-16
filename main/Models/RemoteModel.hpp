#pragma once

#include <stdint.h>
#include "RemoteSettings.hpp"
#include "IRTransmitter.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "lvgl.h"

class RemoteModel {
public:
    // isStoppableActionOngoing should be observed by the bidet, dry, and stop button functions
    explicit RemoteModel();

    // IR Actions
    void smallFlush();
    void fullFlush();
    void stop();

    void setSeatTemperature(RemoteSettings::Temperature level);
    RemoteSettings::Temperature getSeatTemperature();

    void setWaterTemperature(RemoteSettings::Temperature level);
    RemoteSettings::Temperature getWaterTemperature();

    void setDryingTemperature(RemoteSettings::Temperature level);
    RemoteSettings::Temperature getDryingTemperature();

    void setWashMode(RemoteSettings::WashMode mode);
    RemoteSettings::WashMode getWashMode();

    void addWashActionInProgressObserver(lv_observer_cb_t callback, void* data);

    void setPosition(RemoteSettings::PositionMode mode);
    RemoteSettings::PositionMode getPosition();

    void setPressure(RemoteSettings::PressureMode mode);
    RemoteSettings::PressureMode getPressure();

private:
    // For internal use, does not trigger observers.
    void quietStop();

    void startTimeout();
    void stopTimeout();

    TimerHandle_t washModeTimer;
    static void washModeTimerExpired(TimerHandle_t xTimer);

    lv_subject_t washActionInProgress;

    RemoteSettings::WashMode washMode;
    RemoteSettings::PositionMode positionMode;
    RemoteSettings::PressureMode pressureMode;

    RemoteSettings::Temperature seatTemperature;
    RemoteSettings::Temperature waterTemperature;
    RemoteSettings::Temperature dryingTemperature;

    IRTransmitter<32>* irTransmitter;
};
