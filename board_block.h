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
    BOOL contains(int x, int y);
    BoardCell* findCellByXY(int x, int y);
    BoardCell* findCellByLocal(int x, int y);
    void draw();
};

#endif
