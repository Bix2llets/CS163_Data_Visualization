#pragma once
#include "raylib.h"

// PEAK MULTIPLE INHERITANCE
class Toggleable{
    protected:
    bool enabled;
    public:
    Toggleable() : enabled{true} {}
    
    virtual void enable();
    virtual void disable();
    virtual void toggle();
    virtual void set(bool newState);

    bool getState();

};