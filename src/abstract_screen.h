#ifndef ABSTRACT_SCREEN_H
#define ABSTRACT_SCREEN_H

#include <intuition/intuition.h>
#include <proto/intuition.h>
#include <proto/graphics.h>

class AbstractScreen {
protected:
    struct Window *window;
public:    
    AbstractScreen(struct Window *window);
    virtual ~AbstractScreen() {};
    
    virtual void draw() = 0;
    virtual void onClick(int x, int y) = 0;
    virtual void onTimeTick() = 0;    
};

#endif /* ABSTRACT_SCREEN_H */

