#ifndef APPLICATION_H
#define APPLICATION_H

#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/graphics.h>
#include <proto/dos.h>

#include "timer.h"
#include "puzzle.h"

class Application {
private:
    struct GfxBase *gfxBase;
    struct IntuitionBase *intuitionBase;
    struct Window *window;
    Timer *timer;

    Puzzle* createPuzzles();

public:
    Application();
    ~Application();
    void loop();
};

#endif
