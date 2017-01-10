#ifndef APPLICATION_H
#define APPLICATION_H

#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/graphics.h>
#include <proto/dos.h>

class Application {
    struct GfxBase *gfxBase;
    struct IntuitionBase *intuitionBase;
    struct Window *window;

public:
    Application();
    ~Application();

    void loop();
};

#endif
