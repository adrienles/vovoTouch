#pragma once

#include "../Controllers/RemoteController.hpp"
#include "Components/Buttons/FlushButton.hpp"
#include "Config/UITranslation.hpp"
#include <lvgl.h>

#include "Pages/Home.hpp"
#include "Pages/Bidet.hpp"
#include "Pages/Dry.hpp"

class UI {
    public:
        UI(RemoteController* remote);
        ~UI();

        enum class ActionButtons : uint8_t {
            PosteriorContinuous = 0,
            PosteriorRhythm = 1,
            PosteriorTurbo = 2,
            FeminineContinuous = 3,
            FeminineRhythm = 4,
            Drying = 5
        };

    private:
        void createUI();
        void createQuickAccessBar();
        void createTabView();
        void createFlushButton();

        static lv_obj_t* createTab(lv_obj_t* tabview, const char* name);

        static void washActionInProgressCb(lv_observer_t* observer, lv_subject_t* subject);

        static void reloadSettings(lv_observer_t* observer, lv_subject_t* subject);

        void setWashModeInProgress(bool inProgress);

        FlushButton* smallFlushBtn;
        FlushButton* largeFlushBtn;
        FlushButton* stopBtn;

        Home* homePage;
        Bidet* bidetPage;
        Dry* dryingPage;

        UITranslation* translation;

        lv_obj_t* content;

        // Controllers
        RemoteController* remoteController;
};
