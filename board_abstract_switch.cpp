#include "board_abstract_switch.h"

BoardAbstractSwitch::BoardAbstractSwitch(struct Window *window, int value) {
    this->window = window;
    this->value = value;
    this->checked = FALSE;
}

BOOL BoardAbstractSwitch::toggle() {
    this->checked = !this->checked;
    return this->checked;
}
