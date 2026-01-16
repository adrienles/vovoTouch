#include "UI.hpp"
#include "Components/Buttons/Button.hpp"
#include "Components/Buttons/FlushButton.hpp"
#include "Components/Buttons/QuickAccessButton.hpp"
#include "Components/Buttons/RoundButton.hpp"
#include "Pages/Bidet.hpp"
#include "Pages/Home.hpp"
#include "Pages/Dry.hpp"
#include <cstring>
#include <iostream>

#ifdef ESP
    #include "core/lv_obj.h"
    #include "core/lv_obj_pos.h"
    #include "core/lv_obj_style.h"
    #include "core/lv_obj_style_gen.h"
    #include "core/lv_obj_tree.h"
    #include "display/lv_display.h"
    #include "font/lv_font.h"
    #include "layouts/flex/lv_flex.h"
    #include "layouts/lv_layout.h"
    #include "lv_conf_internal.h"
    #include "misc/lv_area.h"
    #include "misc/lv_style.h"
    #include "misc/lv_types.h"
    // #include "others/sysmon/lv_sysmon.h"
    #include "widgets/button/lv_button.h"
    #include "widgets/tabview/lv_tabview.h"
    #include <lvgl.h>
    #include <lvgl_private.h>
#endif

#include "Config/UIConstants.hpp"
#include "Config/UIPalette.hpp"

#define VIEW_BOUNDS(obj)                      \
    lv_obj_set_style_border_width(obj, 1, 0); \
    lv_obj_set_style_border_color(obj, COLOR_STOP_FLUSH, 0);

LV_IMAGE_DECLARE(AutoFlush);
LV_IMAGE_DECLARE(Fan);
LV_IMAGE_DECLARE(UVLED);
LV_IMAGE_DECLARE(SmallFlushMask);
LV_IMAGE_DECLARE(LargeFlushMask);
LV_IMAGE_DECLARE(StopMask);
LV_IMAGE_DECLARE(SmallFlushIcon);
LV_IMAGE_DECLARE(LargeFlushIcon);

LV_FONT_DECLARE(sf_comp_round_bold_24)
LV_FONT_DECLARE(sf_comp_round_bold_16)
LV_FONT_DECLARE(sf_comp_round_semibold_24)

UI::UI(RemoteController* remote) {
    remoteController = remote;
    translation = new UITranslation();

    createUI();

    remoteController->addWashActionInProgressObserver(washActionInProgressCb, this);
}

UI::~UI() {
    if (content != nullptr) {
        lv_obj_delete(content);
        content = nullptr;
    }
}

void UI::createUI() {
    // Screen style
    lv_obj_set_style_bg_color(lv_screen_active(), COLOR_BG, LV_PART_MAIN);

    content = lv_obj_create(lv_screen_active());

    // Content style
    lv_obj_remove_style_all(content);
    lv_obj_set_width(content, lv_pct(100));
    lv_obj_set_height(content, lv_pct(100));
    lv_obj_set_style_pad_top(content, GAP_MD + GAP_SM, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(content, GAP_SM, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(content, GAP_SM, LV_PART_MAIN);

    // Content layout
    lv_obj_set_layout(content, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(content, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(content, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER);

    createQuickAccessBar();

    createTabView();

    createFlushButton();
}

void UI::createQuickAccessBar() {
    lv_obj_t* quickAccess = lv_obj_create(content);

    // Quick access style
    lv_obj_remove_style_all(quickAccess);
    lv_obj_set_width(quickAccess, lv_pct(100));
    lv_obj_set_height(quickAccess, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_gap(quickAccess, GAP_LG, 0);

    // Quick access layout
    lv_obj_set_layout(quickAccess, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(quickAccess, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(quickAccess, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER);

    QuickAccessButton* btnAutoFlush = new QuickAccessButton(quickAccess, &AutoFlush);
    QuickAccessButton* btnDeodorize = new QuickAccessButton(quickAccess, &Fan);
    QuickAccessButton* btnUVLed = new QuickAccessButton(quickAccess, &UVLED);
}

void UI::createTabView() {
    // Tab view
    lv_obj_t* tabView = lv_tabview_create(content);

    // Tab view style
    lv_obj_set_style_pad_gap(tabView, GAP_SM, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(tabView, 0, LV_PART_MAIN);

    // Tab view layout
    lv_obj_set_flex_grow(tabView, 1);
    lv_obj_set_flex_align(tabView, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER);

    // Tab bar
    lv_obj_t* tabBar = lv_tabview_get_tab_bar(tabView);

    // Tab bar style
    lv_obj_set_width(tabBar, LV_SIZE_CONTENT);

    lv_tabview_set_tab_bar_position(tabView, LV_DIR_TOP);
    lv_tabview_set_tab_bar_size(tabView, LV_SIZE_CONTENT);

    lv_obj_set_style_pad_all(tabBar, 3, LV_PART_MAIN);
    lv_obj_set_style_pad_gap(tabBar, 3, LV_PART_MAIN);

    lv_obj_set_style_radius(tabBar, 100, LV_PART_MAIN);

    lv_obj_set_style_bg_color(tabBar, COLOR_WIDGET_BG, LV_PART_MAIN);
    lv_obj_set_style_text_color(tabBar, lv_palette_lighten(LV_PALETTE_GREY, 5),
        0);

    // Tab bar layout
    lv_obj_set_flex_align(tabBar, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER);

    // Tabs
    lv_obj_t* homeTab = createTab(tabView, lv_tr("homePage"));
    homePage = new Home(homeTab);
    // Bidet* homePage = new Bidet(homeTab);
    // lv_obj_t* homePage = lv_obj_create(homeTab);
    // lv_obj_set_size(homePage, lv_pct(100), lv_pct(100));

    lv_obj_t* bidetTab = createTab(tabView, lv_tr("bidetPage"));
    bidetPage = new Bidet(bidetTab, remoteController);

    lv_obj_t* dryingTab = lv_tabview_add_tab(tabView, lv_tr("dryPage"));
    dryingPage = new Dry(dryingTab, remoteController);
    // lv_obj_t* dryingPage = lv_obj_create(homeTab);
    // lv_obj_set_size(dryingPage, lv_pct(100), lv_pct(100));

    int tab_count = lv_tabview_get_tab_count(tabView);

    int maxWidth = 0;
    int textWidths[3];

    for (int i = 0; i < tab_count; i++) {
        lv_obj_t* button = lv_obj_get_child(tabBar, i);

        const char* text = lv_label_get_text(lv_obj_get_child(button, 0));

#ifdef ESP
        lv_text_attributes_t attr = {};
        lv_text_attributes_init(&attr);
#endif

#ifdef ESP
        int itemWidth
            = lv_text_get_width(text, strlen(text), &sf_comp_round_bold_24, &attr);
#else
        int itemWidth = lv_text_get_width(text, strlen(text), &sf_comp_round_bold_24, 0);
#endif

        textWidths[i] = itemWidth;

        if (maxWidth < itemWidth)
            maxWidth = itemWidth;
    }

    for (int i = 0; i < tab_count; i++) {
        lv_obj_t* button = lv_obj_get_child(tabBar, i);

        // Button style
        lv_obj_remove_style_all(button);

        lv_obj_set_width(button, LV_SIZE_CONTENT);

        lv_obj_set_style_text_font(button, &sf_comp_round_bold_24, LV_PART_MAIN);

        lv_obj_set_style_pad_hor(button, GAP_MD + (maxWidth - textWidths[i]) / 2, LV_PART_MAIN);
        lv_obj_set_style_pad_ver(button, GAP_SM, LV_PART_MAIN);

        lv_obj_set_style_radius(button, LV_RADIUS_CIRCLE, 0);

        lv_obj_set_style_bg_color(button, lv_color_lighten(COLOR_WIDGET_BG, 50), LV_PART_MAIN);
        lv_obj_set_style_bg_color(button, COLOR_BTN_PRESSED, LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_bg_opa(button, LV_OPA_0, LV_PART_MAIN);
        lv_obj_set_style_bg_opa(button, LV_OPA_100, LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_bg_opa(button, LV_OPA_100, LV_PART_MAIN | LV_STATE_PRESSED);

        // Button layout
        lv_obj_set_flex_grow(button, 0);

        // Replace default tab switching event to add animation
        lv_obj_remove_event(button, 0);

        auto tabClickedCb = [](lv_event_t* e) {
            lv_obj_t* tabview = static_cast<lv_obj_t*>(lv_event_get_user_data(e));
            lv_obj_t* button = static_cast<lv_obj_t*>(lv_event_get_target(e));

            lv_tabview_set_active(tabview, lv_obj_get_index(button), LV_ANIM_ON);
        };

        lv_obj_add_event_cb(button, tabClickedCb, LV_EVENT_CLICKED, tabView);

        // Button transition
        static const lv_style_prop_t trans_props[] = {
            LV_STYLE_BG_COLOR, LV_STYLE_BG_OPA, 0 /* End marker */
        };

        static lv_style_transition_dsc_t transPressed;
        static lv_style_transition_dsc_t transClicked;

        lv_style_transition_dsc_init(&transClicked, trans_props,
            lv_anim_path_ease_out, 100, 0, NULL);
        lv_style_transition_dsc_init(&transPressed, trans_props,
            lv_anim_path_ease_out, 50, 0, NULL);

        lv_obj_set_style_transition(button, &transClicked, LV_PART_MAIN);
        lv_obj_set_style_transition(button, &transClicked, LV_PART_MAIN | LV_STATE_PRESSED);
    }
}

void UI::createFlushButton() {
    lv_obj_t* flushButtons = lv_obj_create(content);
    lv_obj_remove_style_all(flushButtons);

    lv_obj_set_width(flushButtons, lv_pct(100));
    lv_obj_set_height(flushButtons, 128);

    lv_obj_set_layout(flushButtons, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(flushButtons, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(flushButtons, LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_gap(flushButtons, GAP_SM, LV_PART_MAIN);

    auto smallFlushCb = [](lv_event_t* e) {
        UI* ui = static_cast<UI*>(lv_event_get_user_data(e));
        ui->remoteController->smallFlush();
    };

    smallFlushBtn
        = new FlushButton(flushButtons, &SmallFlushMask, &SmallFlushIcon, COLOR_BTN_SMALL_FLUSH);
    lv_obj_set_flex_grow(smallFlushBtn->getObj(), 4);
    smallFlushBtn->addCallback(smallFlushCb, this);

    auto largeFlushCb = [](lv_event_t* e) {
        UI* ui = static_cast<UI*>(lv_event_get_user_data(e));
        ui->remoteController->fullFlush();
    };

    largeFlushBtn = new FlushButton(flushButtons, &LargeFlushMask, &LargeFlushIcon, COLOR_BTN_LARGE_FLUSH, true);
    lv_obj_set_flex_grow(largeFlushBtn->getObj(), 6);
    largeFlushBtn->addCallback(largeFlushCb, this);

    auto stopCb = [](lv_event_t* e) {
        UI* ui = static_cast<UI*>(lv_event_get_user_data(e));
        std::cout << "Stop button pressed." << std::endl;
        ui->remoteController->stop();
        ui->setWashModeInProgress(false);
    };

    stopBtn = new FlushButton(flushButtons, &StopMask, lv_tr("stopLbl"), COLOR_BTN_STOP);
    lv_obj_set_flex_grow(stopBtn->getObj(), 1);
    stopBtn->addCallback(stopCb, this);

    setWashModeInProgress(false);
}

void UI::washActionInProgressCb(lv_observer_t* observer, lv_subject_t* subject) {
    UI* instance = static_cast<UI*>(lv_observer_get_user_data(observer));
    instance->setWashModeInProgress(static_cast<bool>(lv_subject_get_int(subject)));
}

void UI::reloadSettings(lv_observer_t* observer, lv_subject_t* subject) {
    UI* instance = static_cast<UI*>(lv_observer_get_user_data(observer));

    instance->homePage->reloadSettings();
    instance->bidetPage->reloadSettings();
    instance->dryingPage->reloadSettings();
}

void UI::setWashModeInProgress(bool inProgress) {
    if (inProgress) {
        lv_obj_add_flag(smallFlushBtn->getObj(), LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(largeFlushBtn->getObj(), LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(stopBtn->getObj(), LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_remove_flag(smallFlushBtn->getObj(), LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(largeFlushBtn->getObj(), LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(stopBtn->getObj(), LV_OBJ_FLAG_HIDDEN);
    }
}

lv_obj_t* UI::createTab(lv_obj_t* tabview, const char* name) {
    lv_obj_t* tab = lv_tabview_add_tab(tabview, name);
    lv_obj_remove_style_all(tab);
    lv_obj_set_size(tab, lv_pct(100), lv_pct(100));
    lv_obj_set_style_pad_hor(tab, 62, LV_PART_MAIN);
    return tab;
}