#include <stdio.h>

#include "board.h"

Board::Board(struct Window *window) {
    // printf( "Creating board!\n" );
    this->window = window;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            blocks[i][j] = new BoardBlock(window, i, j);
        }
    }

    for (int i = 0; i < 9; i++) {
        hintSwitches[i] = new BoardHintSwitch(window, i);
        guessSwitches[i] = new BoardGuessSwitch(window, i);
    }

    activeHintSwitch = -1;
    activeGuessSwitch = -1;
}

Board::~Board() {
    // printf( "Destroying board!\n" );
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            delete blocks[i][j];
        }
    }

    for (int i = 0; i < 9; i++) {
        delete hintSwitches[i];
        delete guessSwitches[i];
    }
}

void Board::draw() {
    // printf( "Drawing board!\n" );
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            blocks[i][j]->draw();
        }
    }

    for (int i = 0; i < 9; i++) {
        hintSwitches[i]->draw();
        guessSwitches[i]->draw();
    }
}

int Board::toggleSwitch(int oldValue, int newValue, BoardAbstractSwitch *switches[]) {
    if (newValue == -1) {
        return -1;
    }

    if (oldValue == newValue) {
        switches[newValue]->toggle();
        switches[newValue]->draw();
        return -1;
    }

    if (oldValue != -1) {
        switches[oldValue]->toggle();
        switches[oldValue]->draw();
    }

    switches[newValue]->toggle();
    switches[newValue]->draw();
    return newValue;
}

void Board::updateCell(BoardCell *cell) {
    if (cell->isFixed) {
        return;
    }

    if (activeHintSwitch == -1 && activeGuessSwitch == -1) {
        cell->value = activeGuessSwitch + 1;
        cell->redraw();
    }

    if (activeHintSwitch > -1) {
        cell->hint = cell->hint ^ 1 << activeHintSwitch;
        cell->redraw();
    }

    if (activeGuessSwitch > -1) {
        cell->value = activeGuessSwitch + 1;
        cell->redraw();
    }
}

void Board::onClick(int x, int y) {
    // printf("%d %d\n", x, y);
    if (x <= 9 * Board::CELL_WIDTH) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (blocks[i][j]->contains(x, y)) {
                    BoardCell *cell = blocks[i][j]->BoardBlock::findCellByXY(x, y);
                    if (cell != NULL) {
                        updateCell(cell);
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < 9; i++) {
            if (guessSwitches[i]->contains(x, y)) {
                activeGuessSwitch = toggleSwitch(activeGuessSwitch, i, (BoardAbstractSwitch**)guessSwitches);
                activeHintSwitch = toggleSwitch(activeHintSwitch, activeHintSwitch, (BoardAbstractSwitch**)hintSwitches);
                return;
            }
        }

        for (int i = 0; i < 9; i++) {
            if (hintSwitches[i]->contains(x, y)) {
                activeHintSwitch = toggleSwitch(activeHintSwitch, i, (BoardAbstractSwitch**)hintSwitches);
                activeGuessSwitch = toggleSwitch(activeGuessSwitch, activeGuessSwitch, (BoardAbstractSwitch**)guessSwitches);
                return;
            }
        }
    }
}

void Board::load(Puzzle *puzzle) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    BoardCell *cell = blocks[i][j]->findCellByLocal(k, l);
                    int fixedValue = puzzle->values[3 * j + l][3 * i + k];
                    if (cell != NULL && fixedValue > 0) {
                        cell->isFixed = TRUE;
                        cell->value = fixedValue;
                    }
                }
            }
        }
    }
}
