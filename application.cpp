#include <stdio.h>

#include "application.h"
#include "board.h"

Application::Application() {    
    gfxBase = (struct GfxBase *)OpenLibrary( "graphics.library", 0L );
    
    if ( gfxBase != NULL) {
        intuitionBase = (struct IntuitionBase *)OpenLibrary( "intuition.library", 0L );
    
        if ( intuitionBase != NULL ) {
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
    
            if (window == NULL ) {
                printf( "Unable to open the window!\n" );
                Exit(-1);
            }
        } else {
            printf( "Unable to open the intuition.library!\n" );
            Exit(-2);
        }
    } else {
        printf( "Unable to open the graphics.library!\n" );
        Exit(-3);
    }
}

Application::~Application() {
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
    struct IntuiMessage *message;
    UWORD msgCode;
    ULONG msgClass;
    BOOL end = FALSE;
    
    Board *board = new Board(window);
    board->draw();

    windowSignal = 1L << window->UserPort->mp_SigBit;
        
    while ( !end && window ) {
        signals = Wait( windowSignal );
        
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
    }
    
    delete board;

    return;
}
