#ifndef BOARD_HINT_SWITCH_H
#define BOARD_HINT_SWITCH_H

#include <intuition/intuition.h>
#include <proto/intuition.h>

#include "board_abstract_switch.h"

class BoardHintSwitch : public BoardAbstractSwitch {
public:
    BoardHintSwitch(struct Window *window, int value);
    void draw();
};

#endif
