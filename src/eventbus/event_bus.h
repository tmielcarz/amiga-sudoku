#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include "event_listener.h"
#include "event.h"

class EventBus {
private:
    EventListener *root;
public:
    EventBus();
    ~EventBus();
    
    void registerListener(EventListener *listener);
    void notifyAll(Event e);
};

#endif /* EVENT_BUS_H */

