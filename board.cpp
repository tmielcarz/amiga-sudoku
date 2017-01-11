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

    activeHintSwitch = 0;
    activeGuessSwitch = 0;
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
    if (oldValue == newValue) {
        switches[newValue]->toggle();
        switches[newValue]->draw();
        return 0;
    }

    if (oldValue != 0) {
        switches[oldValue]->toggle();
        switches[oldValue]->draw();
    }
    switches[newValue]->toggle();
    switches[newValue]->draw();
    return newValue;
}

void Board::onClick(int x, int y) {
    // printf("%d %d\n", x, y);
    if (x <= 9 * Board::CELL_WIDTH) {

    } else {
        for (int i = 0; i < 9; i++) {
            if (guessSwitches[i]->contains(x, y)) {
                activeGuessSwitch = toggleSwitch(activeGuessSwitch, i, (BoardAbstractSwitch**)guessSwitches);
                return;
            }
        }

        for (int i = 0; i < 9; i++) {
            if (hintSwitches[i]->contains(x, y)) {
                activeHintSwitch = toggleSwitch(activeHintSwitch, i, (BoardAbstractSwitch**)hintSwitches);
                return;
            }
        }
    }
}
