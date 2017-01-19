#ifndef BOARD_LINE_H
#define BOARD_LINE_H

#include "board_cell.h"

class BoardLine {
private:
    BoardCell *cells[9];
    void markAsInvalid(int value);
public:
    void addCell(int pos, BoardCell *cell);
    void validate();
};

#endif
