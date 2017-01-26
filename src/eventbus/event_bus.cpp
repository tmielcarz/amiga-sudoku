#include "event_bus.h"

#include <stdio.h>

EventBus::EventBus() {
    this->root = NULL;
}

EventBus::~EventBus() {
    
}

void EventBus::registerListener(EventListener *listener) {
    if (this->root == NULL) {
        this->root = listener;
        return;
    }
    
    EventListener *lastListener = this->root;
    while (lastListener->next != NULL) {
        lastListener = lastListener->next;
    }
    
    lastListener->next = listener;
}

void EventBus::notifyAll(Event e) {
    if (this->root == NULL) {
        return;
    }
    
    EventListener *listener = this->root;
    while (listener != NULL) {
        listener->onEvent(e);
        listener = listener->next;
    }    
}