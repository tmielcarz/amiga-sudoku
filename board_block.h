#ifndef BOARD_BLOCK_H
#define BOARD_BLOCK_H

#include <intuition/intuition.h>
#include <proto/intuition.h>

#include "board_cell.h"

class BoardBlock {
    struct Window *window;

    int col;
    int row;

    BoardCell *cells[3][3];
public:
    BoardBlock(struct Window *window, int col, int row);
    ~BoardBlock();
    void draw();
};

#endif
