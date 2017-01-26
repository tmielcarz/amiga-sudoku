#ifndef BOARD_H
#define BOARD_H

#include "../abstract_screen.h"
#include "../puzzle.h"
#include "board_block.h"
#include "board_line.h"
#include "board_cell.h"
#include "board_hint_switch.h"
#include "board_guess_switch.h"

class Board : public AbstractScreen {
private:    
    BoardBlock *blocks[3][3];
    BoardLine *rows[9];
    BoardLine *cols[9];
    BoardHintSwitch *hintSwitches[9];
    BoardGuessSwitch *guessSwitches[9];
    int activeHintSwitch;
    int activeGuessSwitch;
    int elapsedTime;
    BOOL isGameFinished;

    void validate();
    BOOL checkForSuccess();
    void updateTime();
    void updateCell(BoardCell *cell);
    void removeHints(BoardCell *cell);
    void removeHints(BoardLine *line, int value);
    void removeHints(BoardBlock *block, int value);
    void createColsAndRows();
    int toggleSwitch(int oldValue, int newValue, BoardAbstractSwitch *switches[]);    
public:
    static const int CELL_WIDTH = 54;
    static const int CELL_HEIGHT = 27;

    Board(struct Window *window);
    ~Board();    
    void draw();
    void onClick(int x, int y);
    void onTimeTick();
    
    void load(Puzzle *puzzle);    
};

#endif
