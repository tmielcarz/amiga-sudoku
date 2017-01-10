#ifndef BOARD_CELL_H
#define BOARD_CELL_H

#include <intuition/intuition.h>
#include <proto/intuition.h>

class BoardCell {
    struct Window *window;
    int col;
    int row;
public:
    BoardCell(struct Window *window, int col, int row);
    void draw();
};

#endif
