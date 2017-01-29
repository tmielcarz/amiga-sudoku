#include "title_screen.h"

#include <stdio.h>

TitleScreen::TitleScreen(struct Window *window, EventBus *eventBus) : AbstractScreen(window, eventBus) {}

TitleScreen::~TitleScreen() {}

void TitleScreen::draw() {
    SetRast(window->RPort, 0);
    
    struct TextAttr bigFont = { (STRPTR) "ruby.font", 15, FS_NORMAL };
    
    struct IntuiText title = { 1, 0, JAM2, 0, 0, &bigFont, (UBYTE *) "SUDOKU", NULL };
    PrintIText( window->RPort, &title, 320-45, 64 );    
    
    struct TextAttr smallFont = { (STRPTR) "ruby.font", 10, FS_NORMAL };
    
    struct IntuiText author = { 1, 0, JAM2, 0, 0, &smallFont, (UBYTE *) "author: Tomasz 'g0trek' Mielcarz", NULL };
    PrintIText( window->RPort, &author, 320-160, 90 ); 
    
    struct IntuiText version = { 1, 0, JAM2, 0, 0, &smallFont, (UBYTE *) "version: 1.0.0 @ 2017-01-29", NULL };
    PrintIText( window->RPort, &version, 320-130, 110 );        

    struct IntuiText start = { 1, 0, JAM2, 0, 0, &smallFont, (UBYTE *) "press left mouse button to start", NULL };
    PrintIText( window->RPort, &start, 320-150, 150 );            
}

void TitleScreen::onClick(int x, int y) {
    eventBus->notifyAll(Event::NEW_GAME);
}

void TitleScreen::onTimeTick() {
    
}

void TitleScreen::onEvent(Event *e) {
    // printf("Title :: %d\n", e->getType());
}
