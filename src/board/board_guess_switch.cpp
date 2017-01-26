#include "board_abstract_switch.h"
#include "board_guess_switch.h"

BoardGuessSwitch::BoardGuessSwitch(struct Window *window, int value) : BoardAbstractSwitch(window, value) {}

int BoardGuessSwitch::getTopOffset() {
    return 10;
}

int BoardGuessSwitch::getFontColor() {
    return 1;
}

