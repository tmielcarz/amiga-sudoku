#ifndef BOARD_H
#define BOARD_H

#include <intuition/intuition.h>
#include <proto/intuition.h>

#include "board_block.h"
#include "board_hint_switch.h"
#include "board_guess_switch.h"

class Board {
    struct Window *window;
    BoardBlock *blocks[3][3];
    BoardHintSwitch *hintSwitches[9];
    BoardGuessSwitch *guessSwitches[9];
    int activeHintSwitch;
    int activeGuessSwitch;
public:
    static const int CELL_WIDTH = 54;
    static const int CELL_HEIGHT = 27;

    Board(struct Window *window);
    ~Board();
    void draw();
    void onClick(int x, int y);
    int toggleSwitch(int oldValue, int newValue, BoardAbstractSwitch *switches[]);
};

#endif
