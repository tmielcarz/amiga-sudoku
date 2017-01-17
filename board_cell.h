#ifndef BOARD_CELL_H
#define BOARD_CELL_H

#include <intuition/intuition.h>
#include <proto/intuition.h>

class BoardCell {
private:
    struct Window *window;
    int col;
    int row;
public:
    int value;
    int hint;
    BOOL isFixed;

    BoardCell(struct Window *window, int col, int row);
    BOOL contains(int x, int y);
    void draw();
    void redraw();
};

#endif
