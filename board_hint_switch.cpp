#include "board_abstract_switch.h"
#include "board_hint_switch.h"
#include "board.h"

static struct IntuiText ctrlHintNumbers[] = {
    { 3, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "1", NULL },
    { 3, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "2", NULL },
    { 3, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "3", NULL },
    { 3, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "4", NULL },
    { 3, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "5", NULL },
    { 3, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "6", NULL },
    { 3, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "7", NULL },
    { 3, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "8", NULL },
    { 3, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "9", NULL }
};

BoardHintSwitch::BoardHintSwitch(struct Window *window, int value) : BoardAbstractSwitch(window, value) {

}

void BoardHintSwitch::draw() {
    DrawBorder(window->RPort, &singleCtrlNumber, 20 + 9 * Board::CELL_WIDTH + (this->value % 3) * 30, 65 + (this->value / 3) * 15);
    PrintIText(window->RPort, &ctrlHintNumbers[this->value], 20 + 9 * Board::CELL_WIDTH + (this->value % 3) * 30 + 12, 65 + (this->value / 3) * 15 + 4);
}
