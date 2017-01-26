#ifndef EVENT_H
#define EVENT_H

#include <exec/types.h>

class Event {
private:
    SHORT type;
public:
    static const SHORT INITIALIZE  = 0;
    static const SHORT NEW_GAME = 1;
    static const SHORT END_GAME = 2;
    
    Event(SHORT type);
    virtual ~Event() {};
    
    SHORT getType();
};

#endif /* EVENT_H */

