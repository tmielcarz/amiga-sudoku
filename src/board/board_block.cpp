#include <stdio.h>

#include "board_block.h"
#include "board.h"

static SHORT singleBlockPoints[] = {
    1, 1,
    3 * Board::CELL_WIDTH - 1, 1,
    3 * Board::CELL_WIDTH - 1, 3 * Board::CELL_HEIGHT - 1,
    1, 3 * Board::CELL_HEIGHT - 1,
    1, 1
};

static struct Border singleBlock = {
    0, 0,
    1, 0,
    JAM1,
    5, singleBlockPoints,
    NULL
};

BoardBlock::BoardBlock(struct Window *window, int col, int row) {
    // printf( "Creating block [%d, %d]!\n", col, row );
    this->window = window;
    this->col = col;
    this->row = row;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cells[i][j] = new BoardCell(window, 3 * col + i, 3 * row + j);
        }
    }    
}

BoardBlock::~BoardBlock() {
    // printf( "Destroying block [%d, %d]!\n", col, row );
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            delete cells[i][j];
        }
    }
}

void BoardBlock::validate() {
    int blockValues = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ( cells[i][j]->value > 0 ) {
                int cellValue = 1 << cells[i][j]->value;
                if ( (blockValues & cellValue) == 0 ) {
                    blockValues += cellValue;
                } else {
                    markAsInvalid( cells[i][j]->value );
                }
            }
        }
    }
}

void BoardBlock::markAsInvalid(int value) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ( !cells[i][j]->isFixed && cells[i][j]->value == value ) {
                cells[i][j]->isValid = FALSE;
                cells[i][j]->redraw();
            }
        }
    }
}

void BoardBlock::draw() {
    // printf( "Drawing block [%d, %d]!\n", col, row );
    DrawBorder(window->RPort, &singleBlock, Board::X_OFFSET + col * 3 * Board::CELL_WIDTH, Board::Y_OFFSET + row * 3 * Board::CELL_HEIGHT);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cells[i][j]->draw();
        }
    }
}

BOOL BoardBlock::contains(int x, int y) {
    int x0 = Board::X_OFFSET + col * 3 * Board::CELL_WIDTH;
    int x1 = x0 + 3 * Board::CELL_WIDTH;
    int y0 = Board::Y_OFFSET + row * 3 * Board::CELL_HEIGHT;
    int y1 = y0 + 3 * Board::CELL_HEIGHT;

    return (x >= x0 && x < x1 && y >= y0 && y < y1);
}

BoardCell* BoardBlock::findCellByXY(int x, int y) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (cells[i][j]->contains(x, y)) {
                return cells[i][j];
            }
        }
    }

    return NULL;
}

BoardCell* BoardBlock::findCellByLocal(int x, int y) {
    return cells[x][y];
}
