#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "../abstract_screen.h"
#include "../eventbus/event_listener.h"
#include "../eventbus/event.h"

class TitleScreen : public AbstractScreen, public EventListener {
public:
    TitleScreen(struct Window *window, EventBus *eventBus);
    ~TitleScreen();
    void draw();
    void onClick(int x, int y);
    void onTimeTick();
    void onEvent(Event *e);
};

#endif /* TITLE_SCREEN_H */

