#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "event.h"

class EventListener {
public:
    EventListener *next;
    
    EventListener();
    virtual ~EventListener() {};
    virtual void onEvent(Event *e) = 0;
};

#endif /* EVENT_LISTENER_H */

