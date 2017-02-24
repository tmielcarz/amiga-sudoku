#ifndef PUZZLE_SELECT_EVENT_H
#define PUZZLE_SELECT_EVENT_H

#include "../eventbus/event.h"

class PuzzleSelectEvent : public Event {
public:
    char filename[100];
    
    PuzzleSelectEvent();
    virtual ~PuzzleSelectEvent();       
};

#endif

