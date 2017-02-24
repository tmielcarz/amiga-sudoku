#include "puzzle_select_screen.h"
#include "puzzle_select_event.h"
#include <stdio.h>
#include <string.h>
#include <proto/dos.h>
#include <libraries/dos.h>

PuzzleSelectScreen::PuzzleSelectScreen(struct Window *window, EventBus *eventBus) : AbstractScreen(window, eventBus) {}

PuzzleSelectScreen::~PuzzleSelectScreen() {
    selectedFilenameIdx = -1;
    previousFilenameIdx = -1;
}

void PuzzleSelectScreen::draw() {
    SetRast(window->RPort, 0);    
    
    refreshFileList();
    
    struct TextAttr normalFont = { (STRPTR) "topaz.font", 10, FS_NORMAL, FPF_ROMFONT };
    struct TextAttr boldFont = { (STRPTR) "topaz.font", 10, FSF_BOLD, FPF_ROMFONT };
    
    struct IntuiText prompt = { 1, 0, JAM2, 0, 0, &boldFont, (UBYTE *) "Select puzzle:", NULL };
    PrintIText( window->RPort, &prompt, 30, 30 ); 
        
    for (int i = 0; i < filenamesSize; i++) {
        struct IntuiText filename = { 1, 0, JAM2, 0, 0, &normalFont, (UBYTE *) filenames[i], NULL };
        PrintIText( window->RPort, &filename, 40, 45 + (i * 15) ); 
    }        
}

void PuzzleSelectScreen::redraw() {
    struct TextAttr normalFont = { (STRPTR) "topaz.font", 10, FS_NORMAL, FPF_ROMFONT };
    struct TextAttr boldFont = { (STRPTR) "topaz.font", 10, FSF_BOLD, FPF_ROMFONT };

    for (int i = 0; i < filenamesSize; i++) {
        if (i == selectedFilenameIdx || i == previousFilenameIdx) {
            struct IntuiText filename = { 1, 0, JAM2, 0, 0, (i == selectedFilenameIdx) ? &boldFont : &normalFont, (UBYTE *) filenames[i], NULL };
            PrintIText( window->RPort, &filename, 40, 45 + (i * 15) ); 
        }
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

void PuzzleSelectScreen::onMove(int x, int y) {
    if (y < 45 || y > 45 + (filenamesSize * 15)) {
        checkRedraw(-1);
        return;
    }
    
    for (int i = 0; i < filenamesSize; i++) {
        if (y > 45 + (i * 15) && y < 45 + ((i + 1) * 15)) {
            checkRedraw(i);
            return;
        }
    }
}

void PuzzleSelectScreen::checkRedraw(int i) {
    previousFilenameIdx = selectedFilenameIdx;
    selectedFilenameIdx = i;

    if (previousFilenameIdx != selectedFilenameIdx) {
        redraw();
    }    
}

void PuzzleSelectScreen::onClick(int x, int y) {
    if (selectedFilenameIdx != -1) {
        PuzzleSelectEvent *e = new PuzzleSelectEvent();
        strcpy(e->filename, filenames[selectedFilenameIdx]);
        eventBus->notifyAll(e);
        delete e;        
    }
}

void PuzzleSelectScreen::onTimeTick() {
    
}

void PuzzleSelectScreen::onEvent(Event *e) {
    // printf("Title :: %d\n", e->getType());
}
