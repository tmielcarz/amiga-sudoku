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
