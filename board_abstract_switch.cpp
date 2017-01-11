#include "board_abstract_switch.h"
#include "board.h"

BoardAbstractSwitch::BoardAbstractSwitch(struct Window *window, int value) {
    this->window = window;
    this->value = value;
    this->checked = FALSE;
}

BOOL BoardAbstractSwitch::toggle() {
    this->checked = !this->checked;
    return this->checked;
}

void BoardAbstractSwitch::draw() {
    SHORT innerPoints[] = { 1, 1, 29, 1, 29, 14, 1, 14, 1, 1 };
    struct Border innerBorder = {
        0, 0,
        this->checked ? 1 : 0, 0,
        JAM1,
        5, innerPoints,
        NULL
    };

    SHORT outerPoints[] = { 0, 0, 30, 0, 30, 15, 0, 15, 0, 0 };
    struct Border outerBorder = {
        0, 0,
        1, 0,
        JAM1,
        5, outerPoints,
        &innerBorder
    };

    DrawBorder(
        window->RPort, &outerBorder,
        20 + 9 * Board::CELL_WIDTH + (this->value % 3) * 30,
        this->getTopOffset() + (this->value / 3) * 15
    );

    char c[] = {value + 49};
    struct TextAttr font = { (STRPTR) "topaz.font", 8, this->checked ? FSF_BOLD : FS_NORMAL, FPF_ROMFONT };
    struct IntuiText text = { this->getFontColor(), 0, JAM2, 0, 0, &font, (UBYTE *) c, NULL };

    PrintIText(
        window->RPort,
        &text,
        20 + 9 * Board::CELL_WIDTH + (this->value % 3) * 30 + 12,
        this->getTopOffset() + (this->value / 3) * 15 + 4
    );
}

BOOL BoardAbstractSwitch::contains(int x, int y) {
    int x0 = 20 + 9 * Board::CELL_WIDTH + (this->value % 3) * 30;
    int x1 = x0 + 30;
    int y0 = this->getTopOffset() + (this->value / 3) * 15;
    int y1 = y0 + 15;

    return (x >= x0 && x < x1 && y >= y0 && y < y1);
}
