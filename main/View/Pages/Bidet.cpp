#include "Bidet.hpp"

#include "../../Models/RemoteSettings.hpp"
#include "../Components/Tiles/RangeInputTile.hpp"
#include "../Components/Tiles/SliderInputTile.hpp"
#include "../Components/Tiles/WashModeTile.hpp"
#include "../Config/UIConstants.hpp"
#include "../Config/UIPalette.hpp"
#include "../UI.hpp"
#include "lvgl_private.h"

LV_IMAGE_DECLARE(Position);
LV_IMAGE_DECLARE(Pressure);
LV_IMAGE_DECLARE(WaterTemp);
LV_IMAGE_DECLARE(PosteriorWash);
LV_IMAGE_DECLARE(FeminineWash);

void Bidet::createLeftPanel() {
    // Left panel
    leftPanel = lv_obj_create(page);
    lv_obj_remove_style_all(leftPanel);

    // Left panel layout
    lv_obj_set_flex_flow(leftPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_grow(leftPanel, 1);

    lv_obj_set_style_pad_gap(leftPanel, GAP_SM, LV_PART_MAIN);

    lv_obj_set_size(leftPanel, lv_pct(100), lv_pct(100));

    // Temperature slider
    SliderInputTile* temperatureSlider = new SliderInputTile(leftPanel, &WaterTemp, lv_tr("waterTempLbl"), 4);

    // Jet buttons
    posteriorWashButtons = new WashModeTile<true>(leftPanel, &PosteriorWash, lv_tr("posteriorWashLbl"));
    auto& posteriorButtons = posteriorWashButtons->getButtons();
    buttons[0] = posteriorButtons[0]->getObj();
    buttons[1] = posteriorButtons[1]->getObj();
    buttons[2] = posteriorButtons[2]->getObj();

    feminineWashButtons = new WashModeTile<false>(leftPanel, &FeminineWash, lv_tr("feminineWashLbl"));
    auto& feminineButtons = feminineWashButtons->getButtons();
    buttons[3] = feminineButtons[0]->getObj();
    buttons[4] = feminineButtons[1]->getObj();

    for (auto& button : buttons) {
        lv_obj_add_event_cb(button, bidetButtonsClickedCb, LV_EVENT_CLICKED, this);
    }
}

void Bidet::createRightPanel() {
    // Right panel
    rightPanel = lv_obj_create(page);
    lv_obj_remove_style_all(rightPanel);

    // Right panel layout
    lv_obj_set_flex_flow(rightPanel, LV_FLEX_FLOW_COLUMN);

    lv_obj_set_style_pad_gap(rightPanel, GAP_SM, LV_PART_MAIN);

    lv_obj_set_size(rightPanel, LV_SIZE_CONTENT, lv_pct(100));

    // Panel tiles
    RangeInputTile* positionTile = new RangeInputTile(rightPanel, &Position, arrowIcons, positionDots, lv_tr("positionLbl"), 5);
    RangeInputTile* pressureTile = new RangeInputTile(rightPanel, &Pressure, plusMinusIcons, pressureDots, lv_tr("pressureLbl"), 5);
}

void Bidet::bidetButtonsClickedCb(lv_event_t* e) {
    Bidet* instance = static_cast<Bidet*>(lv_event_get_user_data(e));

    lv_obj_t* originatingButton = lv_event_get_target_obj(e);

    if (lv_obj_has_state(originatingButton, LV_STATE_CHECKED)) {

        RemoteSettings::WashMode mode = RemoteSettings::WashMode::Stopped;

        for (uint8_t i = 0; i < instance->buttons.size(); i++) {
            auto& button = instance->buttons[i];

            if (button == lv_event_get_target_obj(e))
                mode = static_cast<RemoteSettings::WashMode>(i);
            else {
                lv_obj_remove_state(button, LV_STATE_CHECKED);
            }
        }

        instance->remoteController->setWashMode(mode);

    } else {
        instance->remoteController->stop();
    }
}

void Bidet::washActionInProgressCb(lv_observer_t* observer, lv_subject_t* subject) {
    Bidet* instance = static_cast<Bidet*>(lv_observer_get_user_data(observer));

    if (static_cast<bool>(lv_subject_get_int(subject)) == false) {
        for (auto& button : instance->buttons) {
            if (lv_obj_has_state(button, LV_STATE_CHECKED))
                lv_obj_remove_state(button, LV_STATE_CHECKED);
        }
    }
}