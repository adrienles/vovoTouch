#include "RoundButton.hpp"
#include "../../Config/UIConstants.hpp"

#ifdef ESP
    #include "core/lv_obj.h"
    #include "core/lv_obj_style_gen.h"
    #include "misc/lv_style.h"
    #include "misc/lv_style_gen.h"
#endif

void RoundButton::setupStyle() {
    lv_obj_set_size(button, 48, 48);
    lv_style_set_radius(&defaultStyle, 24);
}
