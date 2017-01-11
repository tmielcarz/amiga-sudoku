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
    BOOL toggle();
    BOOL contains(int x, int y);
    void draw();

    virtual int getTopOffset() = 0;
    virtual int getFontColor() = 0;
};

#endif
