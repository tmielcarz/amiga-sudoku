#include <stdio.h>

#include "board_line.h"

void BoardLine::addCell(int pos, BoardCell *cell) {
    this->cells[pos] = cell;
}

void BoardLine::validate() {
    int blockValues = 0;
    for (int i = 0; i < 9; i++) {
        if ( cells[i]->value > 0 ) {
            int cellValue = 1 << cells[i]->value;
            if ( (blockValues & cellValue) == 0 ) {
                blockValues += cellValue;
            } else {
                markAsInvalid( cells[i]->value );
            }
        }
    }
}

void BoardLine::markAsInvalid(int value) {
    for (int i = 0; i < 9; i++) {
        if ( !cells[i]->isFixed && cells[i]->value == value ) {
            cells[i]->isValid = FALSE;
            cells[i]->redraw();
        }
    }
}
