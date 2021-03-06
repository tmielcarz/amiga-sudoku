#ifndef BOARD_BLOCK_H
#define BOARD_BLOCK_H

#include <intuition/intuition.h>
#include <proto/intuition.h>

#include "board_cell.h"

class BoardBlock {
private:
    struct Window *window;

    int col;
    int row;

    BoardCell *cells[3][3];

    void markAsInvalid(int value);
public:
    BoardBlock(struct Window *window, int col, int row);
    ~BoardBlock();
    BOOL contains(int x, int y);
    BoardCell* findCellByXY(int x, int y);
    BoardCell* findCellByLocal(int x, int y);
    void draw();
    void validate();
};

#endif
