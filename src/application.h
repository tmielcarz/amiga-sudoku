#ifndef APPLICATION_H
#define APPLICATION_H

#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/graphics.h>
#include <proto/dos.h>

#include "timer.h"
#include "eventbus/event_bus.h"
#include "puzzle.h"
#include "abstract_screen.h"
#include "board/board.h"
#include "title/title_screen.h"
#include "title/puzzle_select_screen.h"

class Application : public EventListener {
private:
    struct GfxBase *gfxBase;
    struct IntuitionBase *intuitionBase;
    struct Window *window;
    struct Screen *screen;
    Timer *timer;
    EventBus *eventBus;
    AbstractScreen *currentScreen;
    TitleScreen *titleScreen;
    PuzzleSelectScreen *puzzleSelectScreen;
    Board *board;

    Puzzle* createPuzzles(char *filename);
public:
    Application();
    ~Application();
    void loop();
    void onEvent(Event *e);
};

#endif
