#include "event.h"

Event::Event(SHORT type) {
    this->type = type;
}

SHORT Event::getType() {
    return this->type;
}
