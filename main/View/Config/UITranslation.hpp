#pragma once

#include <lvgl.h>

class UITranslation
{
public:
    UITranslation()
    {
        static const char *languages[] = {"en", "fr", nullptr};
        static const char *tags[] = {"homePage", "bidetPage", "dryPage", "seatTempLbl", "waterTempLbl", "dryTempLbl", "positionLbl", "pressureLbl", "posteriorWashLbl", "feminineWashLbl", "continuousLbl", "rhythmLbl", "turboLbl", "stopLbl", nullptr};
        static const char *translations[] = {
            "Home", "Accueil",
            "Bidet", "Bidet",
            "Dry", "Séchage",
            "Seat temperature", "Température du siège",
            "Water temperature", "Température de l'eau",
            "Dryer temperature", "Température du séchage",
            "Position", "Position",
            "Pressure", "Pression",
            "Posterior", "Arrière",
            "Feminine", "Féminin",
            "Continuous", "Continu",
            "Rhythm", "Pulsé",
            "Turbo", "Turbo",
            "STOP", "STOP"};

        lv_translation_add_static(languages, tags, translations);
        lv_translation_set_language("fr");
    }
};
