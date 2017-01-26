#include "title_screen.h"

#include <stdio.h>

TitleScreen::TitleScreen(struct Window *window, EventBus *eventBus) : AbstractScreen(window, eventBus) {}

TitleScreen::~TitleScreen() {}

void TitleScreen::draw() {
    SetRast(window->RPort, 0);
    
}

void TitleScreen::onClick(int x, int y) {
    Event *e = new Event(Event::NEW_GAME);
    eventBus->notifyAll(e);
    delete e;    
}

void TitleScreen::onTimeTick() {
    
}

void TitleScreen::onEvent(Event *e) {
    printf("Title :: %d\n", e->getType());
}
