#include "board_abstract_switch.h"
#include "board_hint_switch.h"

BoardHintSwitch::BoardHintSwitch(struct Window *window, int value) : BoardAbstractSwitch(window, value) {}

int BoardHintSwitch::getTopOffset() {
    return 65;
}

int BoardHintSwitch::getFontColor() {
    return 3;
}

