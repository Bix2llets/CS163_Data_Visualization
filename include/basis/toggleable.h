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
    void set(bool newState);

    bool getState();

};