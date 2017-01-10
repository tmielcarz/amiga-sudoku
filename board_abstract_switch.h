#ifndef BOARD_ABSTRACT_SWITCH_H
#define BOARD_ABSTRACT_SWITCH_H

#include <intuition/intuition.h>
#include <proto/intuition.h>

class BoardAbstractSwitch {
public:
    struct Window *window;
    int value;
    BOOL checked;

    BoardAbstractSwitch(struct Window *window, int value);
    virtual void draw() = 0;
    BOOL toggle();
};

static struct TextAttr ctrlNumbersFont = {
    (STRPTR) "topaz.font", 8, FS_NORMAL, FPF_ROMFONT
};

static SHORT singleCtrlNumberPoints[] = {
    0, 0,
    30, 0,
    30, 15,
    0, 15,
    0, 0
};

static struct Border singleCtrlNumber = {
    0, 0,
    1, 0,
    JAM1,
    5, singleCtrlNumberPoints,
    NULL
};

#endif
