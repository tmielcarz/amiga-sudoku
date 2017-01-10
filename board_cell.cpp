#include <stdio.h>

#include "board_cell.h"
#include "board.h"

static SHORT singleCellPoints[] = {
    0, 0,
    Board::CELL_WIDTH, 0,
    Board::CELL_WIDTH, Board::CELL_HEIGHT,
    0, Board::CELL_HEIGHT,
    0, 0
};

static struct Border singleCell = {
    0, 0,
    1, 0,
    JAM1,
    5, singleCellPoints,
    NULL
};

BoardCell::BoardCell(struct Window *window, int col, int row) {
    // printf( "Creating cell [%d, %d]!\n", col, row );
    this->window = window;
    this->col = col;
    this->row = row;
}

void BoardCell::draw() {
    // printf( "Drawing cell [%d, %d]!\n", col, row );
    DrawBorder(window->RPort, &singleCell, col * Board::CELL_WIDTH, row * Board::CELL_HEIGHT);
}
