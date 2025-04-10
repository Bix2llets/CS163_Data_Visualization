#include "animationColor.h"
#pragma once
class DynamicColor: public AnimationColor {
    Color const *startingColor;
    Color const *targetColor;
    public:
    DynamicColor(Color const *startingColor, Color const *targetColor) : startingColor{startingColor}, targetColor{targetColor} {};
    
    void update();
    void setBaseColor(Color const *base);
    void setTargetColor(Color const *target);
    
    void transitionToward(Color const *target);
    void assignColor();
};