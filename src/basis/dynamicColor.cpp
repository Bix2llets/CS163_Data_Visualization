#include "dynamicColor.h"

void DynamicColor::update() {
    assignColor();
    AnimationColor::update();
}

void DynamicColor::setBaseColor(Color const *base) {
    startingColor = base;
    assignColor();
}

void DynamicColor::setTargetColor(Color const *target) {
    targetColor = target;
    assignColor();
}

void DynamicColor::transitionToward(Color const *target) {
    startingColor = targetColor;
    targetColor = target; 
    // factor = 0.f;
    assignColor();
}

void DynamicColor::assignColor() {
    Color base = getBaseColor();
    base = {startingColor->r, startingColor->g, startingColor->b, baseColor.a};
    
    Color target = getTargetColor();
    target.r = targetColor->r;
    target.g = targetColor->g;
    target.b = targetColor->b;
    
    AnimationColor::setBaseColor(base);
    AnimationColor::setTargetColor(target);
    
}