#ifndef BOARD_GUESS_SWITCH_H
#define BOARD_GUESS_SWITCH_H

#include <intuition/intuition.h>
#include <proto/intuition.h>

#include "board_abstract_switch.h"

class BoardGuessSwitch : public BoardAbstractSwitch {
public:
    BoardGuessSwitch(struct Window *window, int value);
    int getTopOffset();
    int getFontColor();
};

#endif
