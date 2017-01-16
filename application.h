#ifndef APPLICATION_H
#define APPLICATION_H

#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/graphics.h>
#include <proto/dos.h>

#include "puzzle.h"

class Application {
    struct GfxBase *gfxBase;
    struct IntuitionBase *intuitionBase;
    struct Window *window;

    struct MsgPort *timerMsgPort;
    struct timerequest *timerIO;
    struct timeval tv;
    ULONG timerSignal;
    BOOL timerWasSent;

    int initTimer();
    void killTimer();
    void sendTimerRequest();
    void readTimerMessage();

    Puzzle* createPuzzles();

public:
    Application();
    ~Application();
    void loop();
};

#endif
