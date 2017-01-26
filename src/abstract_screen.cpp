#include "abstract_screen.h"

AbstractScreen::AbstractScreen(struct Window *window, EventBus *eventBus) {
    this->window = window;
    this->eventBus = eventBus;
}

