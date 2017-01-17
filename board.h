#ifndef BOARD_H
#define BOARD_H

#include <intuition/intuition.h>
#include <proto/intuition.h>

#include "puzzle.h"
#include "board_block.h"
#include "board_cell.h"
#include "board_hint_switch.h"
#include "board_guess_switch.h"

class Board {
private:
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
    void load(Puzzle *puzzle);
    void draw();
    void onClick(int x, int y);
    void updateCell(BoardCell *cell);
    int toggleSwitch(int oldValue, int newValue, BoardAbstractSwitch *switches[]);
};

#endif
