#include <stdio.h>

#include "application.h"
#include "board.h"

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
    
    window = (struct Window *)OpenWindowTags( NULL,
        WA_Left, 0,
        WA_Top, 0,
        WA_Width, 640,
        WA_Height, 256,
        WA_Title, (ULONG)"Sudoku",
        WA_DepthGadget, TRUE,
        WA_CloseGadget, TRUE,
        WA_SizeGadget, TRUE,
        WA_DragBar, TRUE,
        WA_GimmeZeroZero, TRUE,
        WA_ReportMouse, TRUE,
        WA_IDCMP, IDCMP_CLOSEWINDOW | IDCMP_MOUSEBUTTONS | IDCMP_MOUSEMOVE,
        TAG_END );

    if ( window == NULL ) {
        printf( "Unable to open the window!\n" );
        Exit(-3);
    }
    
    timer = new Timer();
	if ( timer->initTimer() != 0 ) {
        printf( "Unable to open the timer!\n" );
        Exit(-4);
	}
}

Application::~Application() {
    timer->killTimer();

    if ( window != NULL ) {
        CloseWindow( window );
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
    Puzzle *puzzle;
    
    puzzle = createPuzzles();

    Board *board = new Board(window);
    board->load(puzzle);
    board->draw();

    windowSignal = 1L << window->UserPort->mp_SigBit;
    timerSignal = 1L << timer->timerMsgPort->mp_SigBit;
        
    int counter = 0;

    while ( !end && window ) {
        signals = Wait( windowSignal | timerSignal );

        /* Check the signal bit for our message port. Will be true if these is a message. */
        if ( signals & windowSignal ) {
            WORD xCoord, yCoord;
        
            /* There may be more than one message, so keep processing messages until there are no more. */
            while ( message = (struct IntuiMessage *)GetMsg(window->UserPort) ) {
                /* Copy the necessary information from the message. */
                msgClass = message->Class;
                msgCode = message->Code;
                xCoord = message->MouseX - window->BorderLeft;
                yCoord = message->MouseY - window->BorderTop;
                
                /* Reply as soon as possible. */
                ReplyMsg((struct Message *)message);
            
                /* Take the proper action in response to the message. */
                switch ( msgClass ) {
                    case IDCMP_CLOSEWINDOW: /* User pressed the close window gadget. */
                        end = TRUE;
                        break;
                    case IDCMP_MOUSEBUTTONS: /* The status of the mouse buttons has changed. */
                        switch ( msgCode ) {
                            case SELECTDOWN: /* The left mouse button has been pressed. */
                                board->onClick(xCoord, yCoord);
                                break;
                        }
                    default:
                        break;
                }
            }
        }

        if ( signals & timerSignal ) {
            timer->readTimerMessage();
            printf("%d \n", counter++);
        }
    }
    
    delete board;

    return;
}

Puzzle* Application::createPuzzles() {
    int values[9][9] = {
        {0, 9, 0, 2, 0, 1, 0, 0, 0},
        {0, 0, 4, 0, 0, 8, 0, 7, 0},
        {0, 7, 0, 0, 6, 9, 0, 0, 8},
        {1, 4, 0, 0, 0, 5, 8, 0, 0},
        {0, 6, 0, 0, 0, 0, 0, 2, 0},
        {0, 0, 8, 6, 0, 0, 0, 4, 7},
        {2, 0, 0, 3, 4, 0, 0, 6, 0},
        {0, 3, 0, 1, 0, 0, 7, 0, 0},
        {0, 0, 0, 8, 0, 2, 0, 1, 0}
    };

    Puzzle *puzzle = new Puzzle(1, values);
    return puzzle;
}
