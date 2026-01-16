#include "RemoteModel.hpp"

#include <iostream>

RemoteModel::RemoteModel() {
    irTransmitter = new IRTransmitter<32>(GPIO_NUM_30);

    lv_subject_init_int(&washActionInProgress, false);

    washModeTimer = xTimerCreate("washModeTimer", pdMS_TO_TICKS(1000 * 5), pdFALSE, static_cast<void*>(this), washModeTimerExpired);
}

void RemoteModel::smallFlush() {
    irTransmitter->transmitCode(0xC8004804);
}

void RemoteModel::fullFlush() {
    irTransmitter->transmitCode(0xC0004004);
}

void RemoteModel::stop() {
    irTransmitter->transmitCode(0x00154500);
    lv_subject_set_int(&washActionInProgress, false);
    if (xTimerIsTimerActive(washModeTimer) != pdFALSE)
        stopTimeout();
    std::cout << "Action stopped!" << std::endl;
}

void RemoteModel::quietStop() {
    irTransmitter->transmitCode(0x00154500);
}

void RemoteModel::setSeatTemperature(RemoteSettings::Temperature level) {
    seatTemperature = level;

    switch (seatTemperature) {
        case RemoteSettings::Temperature::Low:
            irTransmitter->transmitCode(0x68414904);
            break;
        case RemoteSettings::Temperature::MediumLow:
            irTransmitter->transmitCode(0x68814904);
            break;
        case RemoteSettings::Temperature::MediumHigh:
            irTransmitter->transmitCode(0x68C14904);
            break;
        case RemoteSettings::Temperature::High:
            irTransmitter->transmitCode(0x68014904);
            break;
    }
}

void RemoteModel::setWaterTemperature(RemoteSettings::Temperature level) {
    waterTemperature = level;

    switch (waterTemperature) {
        case RemoteSettings::Temperature::Low:
            irTransmitter->transmitCode(0x78114904);
            break;
        case RemoteSettings::Temperature::MediumLow:
            irTransmitter->transmitCode(0x78214904);
            break;
        case RemoteSettings::Temperature::MediumHigh:
            irTransmitter->transmitCode(0x78314904);
            break;
        case RemoteSettings::Temperature::High:
            irTransmitter->transmitCode(0x78014904);
            break;
    }
}

void RemoteModel::setDryingTemperature(RemoteSettings::Temperature level) {
    dryingTemperature = level;

    switch (dryingTemperature) {
        case RemoteSettings::Temperature::Low:
            irTransmitter->transmitCode(0x88154D04);
            break;
        case RemoteSettings::Temperature::MediumLow:
            irTransmitter->transmitCode(0x88194104);
            break;
        case RemoteSettings::Temperature::MediumHigh:
            irTransmitter->transmitCode(0x881D4504);
            break;
        case RemoteSettings::Temperature::High:
            irTransmitter->transmitCode(0x88114904);
            break;
    }
}

void RemoteModel::setWashMode(RemoteSettings::WashMode mode) {
    washMode = mode;

    if (washMode == RemoteSettings::WashMode::Stopped) {
        stop();
        return;
    } else {
        quietStop();
    }

    switch (washMode) {
        case RemoteSettings::WashMode::Stopped:
            break;
        case RemoteSettings::WashMode::PosteriorContinuous:
            irTransmitter->transmitCode(0x8154D00);
            break;
        case RemoteSettings::WashMode::PosteriorRhythm:
            irTransmitter->transmitCode(0x8154D00);
            irTransmitter->transmitCode(0x8154D00);
            break;
        case RemoteSettings::WashMode::PosteriorTurbo:
            irTransmitter->transmitCode(0x10154500);
            break;
        case RemoteSettings::WashMode::FeminineContinuous:
            irTransmitter->transmitCode(0x18154D00);
            break;
        case RemoteSettings::WashMode::FeminineRhythm:
            irTransmitter->transmitCode(0x18154D00);
            irTransmitter->transmitCode(0x18154D00);
            break;
        case RemoteSettings::WashMode::Drying:
            irTransmitter->transmitCode(0x20154500);
            break;
    }

    lv_subject_set_int(&washActionInProgress, true);

    startTimeout();
}

void RemoteModel::addWashActionInProgressObserver(lv_observer_cb_t callback, void* data) {
    lv_subject_add_observer(&washActionInProgress, callback, data);
}

void RemoteModel::setPosition(RemoteSettings::PositionMode mode) {
    positionMode = mode;

    switch (positionMode) {
        case RemoteSettings::PositionMode::UpFront:
            irTransmitter->transmitCode(0x58154D04);
            break;
        case RemoteSettings::PositionMode::Front:
            irTransmitter->transmitCode(0x60154503);
            break;
        case RemoteSettings::PositionMode::Middle:
            irTransmitter->transmitCode(0x60154502);
            break;
        case RemoteSettings::PositionMode::Back:
            irTransmitter->transmitCode(0x60154501);
            break;
        case RemoteSettings::PositionMode::FarBack:
            irTransmitter->transmitCode(0x60154500);
            break;
    }
    // 1 down 0b01011000000101010100110100000100
    // 1 up   0b01100000000101010100010100000011
    // 2 up   0b01100000000101010100010100000010
    // 3 up   0b01100000000101010100010100000001
    // 4 up   0b01100000000101010100010100000000
    // 5 up   0b01100000000101010100010100000000
    // 5 down 0b01011000000101010100110100000001
    // 4 down 0b01011000000101010100110100000010
    // 3 down 0b01011000000101010100110100000011
    // 2 down 0b01011000000101010100110100000100
    // 1 down 0b01011000000101010100110100000100
}

void RemoteModel::setPressure(RemoteSettings::PressureMode mode) {
    pressureMode = mode;

    switch (pressureMode) {
        case RemoteSettings::PressureMode::Lowest:
            irTransmitter->transmitCode(0x0);
            break;
        case RemoteSettings::PressureMode::Low:
            irTransmitter->transmitCode(0x0);
            break;
        case RemoteSettings::PressureMode::Medium:
            irTransmitter->transmitCode(0x0);
            break;
        case RemoteSettings::PressureMode::High:
            irTransmitter->transmitCode(0x0);
            break;
        case RemoteSettings::PressureMode::Highest:
            irTransmitter->transmitCode(0x0);
            break;
    }
}

void RemoteModel::washModeTimerExpired(TimerHandle_t xTimer) {
    auto instance = static_cast<RemoteModel*>(pvTimerGetTimerID(xTimer));

    std::cout << "Timer has expired!" << std::endl;
    if (instance)
        instance->stop();
}

void RemoteModel::startTimeout() {
    if (xTimerReset(washModeTimer, 50) != pdFAIL)
        std::cout << "Timer has been started!" << std::endl;
    else
        std::cout << "Timer start attempt was unsuccessful." << std::endl;
}

void RemoteModel::stopTimeout() {
    if (xTimerStop(washModeTimer, 50) != pdFAIL)
        std::cout << "Timer has been stopped!" << std::endl;
    else
        std::cout << "Timer stop attempt was unsuccessful." << std::endl;
}
