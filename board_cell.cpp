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

static struct TextAttr font = { (STRPTR) "topaz.font", 8, FS_NORMAL, FPF_ROMFONT };

static struct IntuiText hintsOn[] = {
    { 3, 0, JAM2, -Board::CELL_WIDTH / 2 + 2, -11, &font, (UBYTE *) "1", NULL },
    { 3, 0, JAM2, -3, -11, &font, (UBYTE *) "2", NULL },
    { 3, 0, JAM2, Board::CELL_WIDTH / 2 - 9, -11, &font, (UBYTE *) "3", NULL },
    { 3, 0, JAM2, -Board::CELL_WIDTH / 2 + 2, -3, &font, (UBYTE *) "4", NULL },
    { 3, 0, JAM2, -3, -3, &font, (UBYTE *) "5", NULL },
    { 3, 0, JAM2, Board::CELL_WIDTH / 2 - 9, -3, &font, (UBYTE *) "6", NULL },
    { 3, 0, JAM2, -Board::CELL_WIDTH / 2 + 2, 5, &font, (UBYTE *) "7", NULL },
    { 3, 0, JAM2, -3, 5, &font, (UBYTE *) "8", NULL },
    { 3, 0, JAM2, Board::CELL_WIDTH / 2 - 9, 5, &font, (UBYTE *) "9", NULL }
};

static struct IntuiText hintsOff[] = {
    { 0, 0, JAM2, -Board::CELL_WIDTH / 2 + 2, -11, &font, (UBYTE *) "1", NULL },
    { 0, 0, JAM2, -3, -11, &font, (UBYTE *) "2", NULL },
    { 0, 0, JAM2, Board::CELL_WIDTH / 2 - 9, -11, &font, (UBYTE *) "3", NULL },
    { 0, 0, JAM2, -Board::CELL_WIDTH / 2 + 2, -3, &font, (UBYTE *) "4", NULL },
    { 0, 0, JAM2, -3, -3, &font, (UBYTE *) "5", NULL },
    { 0, 0, JAM2, Board::CELL_WIDTH / 2 - 9, -3, &font, (UBYTE *) "6", NULL },
    { 0, 0, JAM2, -Board::CELL_WIDTH / 2 + 2, 5, &font, (UBYTE *) "7", NULL },
    { 0, 0, JAM2, -3, 5, &font, (UBYTE *) "8", NULL },
    { 0, 0, JAM2, Board::CELL_WIDTH / 2 - 9, 5, &font, (UBYTE *) "9", NULL }
};

BoardCell::BoardCell(struct Window *window, int col, int row) {
    // printf( "Creating cell [%d, %d]!\n", col, row );
    this->window = window;
    this->col = col;
    this->row = row;
    this->value = 0;
    this->hint = 0;
    this->isFixed = FALSE;
    this->isValid = TRUE;
}

void BoardCell::draw() {
    DrawBorder(window->RPort, &singleCell, col * Board::CELL_WIDTH, row * Board::CELL_HEIGHT);

    if (isFixed) {
        char c[1];
        c[0] = value + 48;
        struct IntuiText text = { 2, 0, JAM2, 0, 0, &font, (UBYTE *) c, NULL };

        PrintIText(
            window->RPort, &text,
            col * Board::CELL_WIDTH + Board::CELL_WIDTH / 2 - 4,
            row * Board::CELL_HEIGHT + Board::CELL_HEIGHT / 2 - 4
        );
    }
}

void BoardCell::redraw() {
    // printf( "Drawing cell [%d, %d]!\n", col, row );
    DrawBorder(window->RPort, &singleCell, col * Board::CELL_WIDTH, row * Board::CELL_HEIGHT);

    char c[3];
    c[0] = 32;
    c[1] = 32;
    c[2] = 0;
    struct IntuiText text = { 1, 0, JAM2, 0, 0, &font, (UBYTE *) c, NULL };

    PrintIText(
        window->RPort, &text,
        col * Board::CELL_WIDTH + Board::CELL_WIDTH / 2 - 4,
        row * Board::CELL_HEIGHT + Board::CELL_HEIGHT / 2 - 4
    );

    int i;
    for (i = 0; i < 9; i++) {
        IntuiText text = (value > 0 || ((hint & (1 << i)) == 0)) ? hintsOff[i] : hintsOn[i];
        PrintIText(
            window->RPort, &text,
            col * Board::CELL_WIDTH + Board::CELL_WIDTH / 2,
            row * Board::CELL_HEIGHT + Board::CELL_HEIGHT / 2
        );
    }

    if (value > 0) {
        char c[3];
        
        if (isValid) {
            c[0] = value + 48;
            c[1] = 0;
        } else {
            c[0] = value + 48;
            c[1] = '!';
            c[2] = 0;
        }

        struct IntuiText text = { 1, 0, JAM2, 0, 0, &font, (UBYTE *) c, NULL };
    
        PrintIText(
            window->RPort, &text,
            col * Board::CELL_WIDTH + Board::CELL_WIDTH / 2 - 4, 
            row * Board::CELL_HEIGHT + Board::CELL_HEIGHT / 2 - 4
        );
    }
}

BOOL BoardCell::contains(int x, int y) {
    int x0 = col * Board::CELL_WIDTH;
    int x1 = x0 + Board::CELL_WIDTH;
    int y0 = row * Board::CELL_HEIGHT;
    int y1 = y0 + Board::CELL_HEIGHT;

    return (x >= x0 && x < x1 && y >= y0 && y < y1);
}
