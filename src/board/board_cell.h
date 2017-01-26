#ifndef BOARD_CELL_H
#define BOARD_CELL_H

#include <intuition/intuition.h>
#include <proto/intuition.h>

class BoardCell {
private:
    struct Window *window;
public:
    int col;
    int row;
    int value;
    int hint;
    BOOL isFixed;
    BOOL isValid;

    BoardCell(struct Window *window, int col, int row);
    BOOL contains(int x, int y);
    void draw();
    void redraw();
};

#endif
