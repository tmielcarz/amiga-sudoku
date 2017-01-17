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
    elapsedTime = 0;
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

    updateTime();
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

void Board::validate() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    BoardCell *cell = blocks[i][j]->findCellByLocal(k, l);
                    if ( !cell->isFixed && !cell->isValid ) {
                        cell->isValid = TRUE;
                        cell->redraw();
                    }
                }
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            blocks[i][j]->validate();
        }
    }

    // TODO validate cols and rows

    // TODO check finish condition
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

    validate();
}

void Board::updateTime() {
    int seconds = elapsedTime % 60;
    int minutes = elapsedTime / 60;

    char strSeconds[3];
    if ( seconds < 10 ) {
        sprintf( strSeconds, "0%d", seconds);
    } else {
        sprintf( strSeconds, "%d", seconds);
    }

    char strMinutes[3];
    if ( minutes < 10 ) {
        sprintf( strMinutes, "0%d", minutes);
    } else {
        sprintf( strMinutes, "%d", minutes);
    }

    char strTime[6];
    sprintf( strTime, "%s:%s", strMinutes, strSeconds );
    
    struct TextAttr font = { (STRPTR) "topaz.font", 8, FS_NORMAL };
    struct IntuiText text = { 1, 0, JAM2, 0, 0, &font, (UBYTE *) strTime, NULL };

    PrintIText(
        window->RPort, &text,
        20 + 9 * Board::CELL_WIDTH + 30,
        9 * Board::CELL_HEIGHT - 16
    );
}

void Board::onTimeTick() {
    elapsedTime++;
    updateTime();
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
