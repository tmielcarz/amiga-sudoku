#include "board_abstract_switch.h"
#include "board_guess_switch.h"
#include "board.h"

static struct IntuiText ctrlGuessNumbers[] = {
    { 1, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "1", NULL },
    { 1, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "2", NULL },
    { 1, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "3", NULL },
    { 1, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "4", NULL },
    { 1, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "5", NULL },
    { 1, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "6", NULL },
    { 1, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "7", NULL },
    { 1, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "8", NULL },
    { 1, 0, JAM2, 0, 0, &ctrlNumbersFont, (UBYTE *) "9", NULL }
};

BoardGuessSwitch::BoardGuessSwitch(struct Window *window, int value) : BoardAbstractSwitch(window, value) {

}

void BoardGuessSwitch::draw() {
    DrawBorder(window->RPort, &singleCtrlNumber, 20 + 9 * Board::CELL_WIDTH + (this->value % 3) * 30, 10 + (this->value / 3) * 15);
    PrintIText(window->RPort, &ctrlGuessNumbers[this->value], 20 + 9 * Board::CELL_WIDTH + (this->value % 3) * 30 + 12, 10 + (this->value / 3) * 15 + 4);
}
