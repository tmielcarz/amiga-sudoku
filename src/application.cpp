#include <stdio.h>

#include "application.h"
#include "title/puzzle_select_event.h"

Application::Application() {    
    gfxBase = (struct GfxBase *)OpenLibrary( "graphics.library", 0L );
    if ( gfxBase == NULL ) {
        printf( "Unable to open the graphics.library!\n" );
        Exit(-1);
    }
    
    intuitionBase = (struct IntuitionBase *)OpenLibrary( "intuition.library", 0L );
    if ( intuitionBase == NULL ) {
        printf( "Unable to open the intuition.library!\n" );
        Exit(-2);
    }
    
    struct NewScreen screenDef = {
        0, 0,
        640, 256,
        2, 
        0, 1,
        HIRES,
        CUSTOMSCREEN | SCREENQUIET,
        NULL,
        NULL,
        NULL,
        NULL,        
    };
    
    struct NewWindow windowDef = { 
        0, 0, 
        640, 256, 
        0, 1, 
        IDCMP_CLOSEWINDOW | IDCMP_MOUSEBUTTONS | IDCMP_MOUSEMOVE | IDCMP_RAWKEY, 
        GIMMEZEROZERO | REPORTMOUSE | ACTIVATE | SMART_REFRESH, 
        NULL, NULL, 
        NULL, 
        NULL, NULL, 
        100, 50, 
        640, 256, 
        CUSTOMSCREEN,
    };       
    
    screen = (struct Screen *)OpenScreen(&screenDef);
    if ( screen == NULL ) {
        printf( "Unable to open the screen!\n" );
        Exit(-3);
    }
    
    windowDef.Screen = screen;
    
    window = (struct Window *)OpenWindow(&windowDef);
    if ( window == NULL ) {
        printf( "Unable to open the window!\n" );
        Exit(-4);
    }
    
    timer = new Timer();
    if ( timer->initTimer() != 0 ) {
        printf( "Unable to open the timer!\n" );
        Exit(-5);
    }
    
    eventBus = new EventBus();
    
    currentScreen = NULL;
    board = new Board(window, eventBus);
    titleScreen = new TitleScreen(window, eventBus);
    puzzleSelectScreen = new PuzzleSelectScreen(window, eventBus);
                    
    eventBus->registerListener((EventListener*) this);
    eventBus->registerListener((EventListener*) board);
    eventBus->registerListener((EventListener*) titleScreen);
    eventBus->registerListener((EventListener*) puzzleSelectScreen);    
}

Application::~Application() {        
    delete eventBus;
    
    delete board;
    
    delete titleScreen;
    
    delete puzzleSelectScreen;
    
    timer->killTimer();

    if ( window != NULL ) {
        CloseWindow( window );
    }

    if ( screen != NULL ) {
        CloseScreen( screen );
    }
    
    if ( intuitionBase != NULL ) {
        CloseLibrary( (struct Library *)intuitionBase );
    }
    
    if ( gfxBase != NULL ) {
        CloseLibrary( (struct Library *)gfxBase );
    }
}

void Application::loop() {
    ULONG signals;
    ULONG windowSignal;
    ULONG timerSignal;
    struct IntuiMessage *message;
    UWORD msgCode;
    ULONG msgClass;
    BOOL end = FALSE;
            
    eventBus->notifyAll(Event::INITIALIZE);
    
    windowSignal = 1L << window->UserPort->mp_SigBit;
    timerSignal = 1L << timer->timerMsgPort->mp_SigBit;
        
    while ( !end && window ) {
        signals = Wait( windowSignal | timerSignal );

        if ( signals & windowSignal ) {
            WORD xCoord, yCoord;
        
            while ( (message = (struct IntuiMessage *)GetMsg(window->UserPort)) ) {
                msgClass = message->Class;
                msgCode = message->Code;
                xCoord = message->MouseX - window->BorderLeft;
                yCoord = message->MouseY - window->BorderTop;
                
                ReplyMsg((struct Message *)message);
            
                switch ( msgClass ) {
                    case IDCMP_RAWKEY:
                        if (msgCode == 69) { // ESC
                            end = TRUE;
                        }
                        break;
                    case IDCMP_CLOSEWINDOW:
                        end = TRUE;
                        break;
                    case IDCMP_MOUSEMOVE:
                        // printf("MOVE %d %d\n", xCoord, yCoord);
                        if (currentScreen != NULL) {
                            currentScreen->onMove(xCoord, yCoord);
                        }                        
                        break;
                    case IDCMP_MOUSEBUTTONS:
                        // printf("BUTTON %d %d\n", xCoord, yCoord);
                        switch ( msgCode ) {
                            case SELECTDOWN:
                                if (currentScreen != NULL) {
                                    currentScreen->onClick(xCoord, yCoord);
                                }
                                break;
                        }
                    default:
                        break;
                }
            }
        }

        if ( signals & timerSignal ) {
            timer->readTimerMessage();
            if (currentScreen != NULL) {
                currentScreen->onTimeTick();
            }
        }
    }        

    return;
}

void Application::onEvent(Event *e) {
    // printf("Application :: %d\n", e->getType());
    
    if (e->getType() == Event::INITIALIZE) {
        currentScreen = titleScreen;
        currentScreen->draw();        
    }
    
    if (e->getType() == Event::NEW_GAME) {        
        currentScreen = puzzleSelectScreen;
        currentScreen->draw();
    }
    
    if (e->getType() == Event::PUZZLE_SELECTED) {
        PuzzleSelectEvent *pse = (PuzzleSelectEvent *)e;
        
        Puzzle *puzzle;    
        puzzle = createPuzzles(pse->filename);
        
        board->load(puzzle);
        currentScreen = board;
        currentScreen->draw();        
    }

    if (e->getType() == Event::END_GAME) {
        
    }    
}

Puzzle* Application::createPuzzles(char* filename) {    
    FILE *input;
    int values[9][9];
        
    input = fopen(filename, "r");
    for (int i = 0; i < 9; i++) {
        fscanf(input, "%d %d %d %d %d %d %d %d %d", &values[i][0], &values[i][1], &values[i][2], &values[i][3], &values[i][4], &values[i][5], &values[i][6], &values[i][7], &values[i][8]);
    }    
    fclose(input);
    
    Puzzle *puzzle = new Puzzle(1, values);
    return puzzle;
}
