#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "../abstract_screen.h"

class TitleScreen : public AbstractScreen {
public:
    TitleScreen(struct Window *window);
    ~TitleScreen();
    void draw();
    void onClick(int x, int y);
    void onTimeTick();
};

#endif /* TITLE_SCREEN_H */

