#include "toggleable.h"


void Toggleable::enable() {
    enabled = true;
}
void Toggleable::disable() {
    enabled = false;
}
void Toggleable::toggle() {
    enabled = !enabled;
}
void Toggleable::set(bool newState) {
    enabled = newState;
}

bool Toggleable::getState() {
    return enabled;
}