#include "title_screen.h"

TitleScreen::TitleScreen(struct Window *window) : AbstractScreen(window) {}

TitleScreen::~TitleScreen() {}

void TitleScreen::draw() {
    SetRast(window->RPort, 0);
    
}

void TitleScreen::onClick(int x, int y) {
    
}

void TitleScreen::onTimeTick() {
    
}

