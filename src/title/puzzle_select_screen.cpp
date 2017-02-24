#include "puzzle_select_screen.h"
#include "puzzle_select_event.h"
#include <stdio.h>
#include <string.h>
#include <proto/dos.h>
#include <libraries/dos.h>

PuzzleSelectScreen::PuzzleSelectScreen(struct Window *window, EventBus *eventBus) : AbstractScreen(window, eventBus) {}

PuzzleSelectScreen::~PuzzleSelectScreen() {}

void PuzzleSelectScreen::draw() {
    SetRast(window->RPort, 0);    
    
    refreshFileList();
    
    struct TextAttr smallFont = { (STRPTR) "ruby.font", 10, FS_NORMAL };
    
    struct IntuiText prompt = { 1, 0, JAM2, 0, 0, &smallFont, (UBYTE *) "Select puzzle:", NULL };
    PrintIText( window->RPort, &prompt, 30, 30 ); 
        
    for (int i = 0; i < filenamesSize; i++) {
        struct IntuiText filename = { 1, 0, JAM2, 0, 0, &smallFont, (UBYTE *) filenames[i], NULL };
        PrintIText( window->RPort, &filename, 40, 45 + (i * 15) ); 
    }
}

void PuzzleSelectScreen::refreshFileList() {
    struct FileInfoBlock fi;
    long lock = Lock("PROGDIR:", ACCESS_READ);
    
    filenamesSize = 0;
    if (Examine(lock, &fi)) {
        do {
            char *dot = strrchr(fi.fib_FileName, '.');
            if (dot && !strcmp(dot, ".dat")) {
                strcpy(filenames[filenamesSize], fi.fib_FileName);
                filenamesSize++;
            }
        } while (ExNext(lock, &fi));
    }    
}

void PuzzleSelectScreen::onClick(int x, int y) {    
    PuzzleSelectEvent *e = new PuzzleSelectEvent();
    strcpy(e->filename, "puzzle_1.dat");
    eventBus->notifyAll(e);
    delete e;        
}

void PuzzleSelectScreen::onTimeTick() {
    
}

void PuzzleSelectScreen::onEvent(Event *e) {
    // printf("Title :: %d\n", e->getType());
}
