#ifndef BOARD_LINE_H
#define BOARD_LINE_H

#include "board_cell.h"

class BoardLine {
private:
    void markAsInvalid(int value);
public:
    BoardCell *cells[9];
    void addCell(int pos, BoardCell *cell);
    void validate();
};

#endif
