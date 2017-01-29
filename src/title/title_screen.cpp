#include "title_screen.h"

#include <stdio.h>

TitleScreen::TitleScreen(struct Window *window, EventBus *eventBus) : AbstractScreen(window, eventBus) {}

TitleScreen::~TitleScreen() {}

void TitleScreen::draw() {
    SetRast(window->RPort, 0);
    
    struct TextAttr font = { (STRPTR) "topaz.font", 8, FS_NORMAL };
    struct IntuiText text = { 1, 0, JAM2, 0, 0, &font, (UBYTE *) "SUDOKU", NULL };

    PrintIText(
        window->RPort, &text,
        296, 64
    );    
}

void TitleScreen::onClick(int x, int y) {
    eventBus->notifyAll(Event::NEW_GAME);
}

void TitleScreen::onTimeTick() {
    
}

void TitleScreen::onEvent(Event *e) {
    printf("Title :: %d\n", e->getType());
}
