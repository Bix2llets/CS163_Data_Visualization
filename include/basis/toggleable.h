#pragma once
#include "raylib.h"

// PEAK MULTIPLE INHERITANCE
class Toggleable{
    protected:
    bool enabled;
    public:
    Toggleable() : enabled{true} {}
    
    void enable();
    void disable();
    void toggle();
    bool isEnabled() { return enabled; }
    void set(bool newState);

    bool getState();

};