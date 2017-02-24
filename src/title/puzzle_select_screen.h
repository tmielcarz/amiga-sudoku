#ifndef PUZZLE_SELECT_SCREEN_H
#define PUZZLE_SELECT_SCREEN_H

#include "../abstract_screen.h"
#include "../eventbus/event_listener.h"
#include "../eventbus/event.h"

class PuzzleSelectScreen : public AbstractScreen, public EventListener {
public:
    PuzzleSelectScreen(struct Window *window, EventBus *eventBus);
    ~PuzzleSelectScreen();
    void draw();
    void onClick(int x, int y);
    void onTimeTick();
    void onEvent(Event *e);
private:
    char filenamesSize;
    char filenames[100][100];   
    void refreshFileList();
};

#endif

