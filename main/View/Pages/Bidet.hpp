#pragma once

#include "Page.hpp"
#include <lvgl.h>
#include "../Components/Tiles/WashModeTile.hpp"
#include "../../Controllers/RemoteController.hpp"

LV_IMAGE_DECLARE(PositionDot0);
LV_IMAGE_DECLARE(PositionDot1);
LV_IMAGE_DECLARE(PositionDot2);
LV_IMAGE_DECLARE(PositionDot3);
LV_IMAGE_DECLARE(PositionDot4);
LV_IMAGE_DECLARE(PressureDot0);
LV_IMAGE_DECLARE(PressureDot1);
LV_IMAGE_DECLARE(PressureDot2);
LV_IMAGE_DECLARE(PressureDot3);
LV_IMAGE_DECLARE(PressureDot4);
LV_IMAGE_DECLARE(Plus);
LV_IMAGE_DECLARE(Minus);
LV_IMAGE_DECLARE(DownArrow);
LV_IMAGE_DECLARE(UpArrow);

class Bidet : public Page
{
public:
  explicit Bidet(lv_obj_t *parent, RemoteController* remote) : Page(parent), remoteController(remote)
  {
    createLeftPanel();
    createRightPanel();

    remoteController->addWashActionInProgressObserver(washActionInProgressCb, this);
  }

  ~Bidet() = default;

  void reloadSettings();

private:
  void createLeftPanel();
  void createRightPanel();

  static void bidetButtonsClickedCb(lv_event_t* e);

  static void washActionInProgressCb(lv_observer_t* observer, lv_subject_t* subject);

  lv_obj_t *leftPanel;
  lv_obj_t *rightPanel;

  WashModeTile<true>* posteriorWashButtons;
  WashModeTile<false>* feminineWashButtons;

  std::array<lv_obj_t*, 5> buttons;

  const lv_img_dsc_t *arrowIcons[2] = {&UpArrow, &DownArrow};
  const lv_img_dsc_t *plusMinusIcons[2] = {&Plus, &Minus};

  const lv_img_dsc_t *positionDots[5] = {&PositionDot4, &PositionDot3, &PositionDot2, &PositionDot1, &PositionDot0};
  const lv_img_dsc_t *pressureDots[5] = {&PressureDot0, &PressureDot1, &PressureDot2, &PressureDot3, &PressureDot4};

  RemoteController* remoteController;
};
