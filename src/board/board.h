#ifndef BOARD_H
#define BOARD_H

#include "../abstract_screen.h"
#include "../puzzle.h"
#include "../eventbus/event_listener.h"
#include "../eventbus/event.h"
#include "board_block.h"
#include "board_line.h"
#include "board_cell.h"
#include "board_hint_switch.h"
#include "board_guess_switch.h"

class Board : public AbstractScreen, public EventListener {
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
    static const int X_OFFSET = 10;
    static const int Y_OFFSET = 5;

    Board(struct Window *window, EventBus *eventBus);
    ~Board();    
    void draw();
    void onClick(int x, int y);
    void onMove(int x, int y);
    void onTimeTick();
    void onEvent(Event *e);    
    
    void load(Puzzle *puzzle);    
};

#endif
