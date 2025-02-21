#include "animationColor.h"

void AnimationColor::setTargetColor(Color color) { targetColor = color; }

void AnimationColor::setBaseColor(Color color) { baseColor = color; }

void AnimationColor::setCurrentColor(Color color) { currentColor = color; }

void AnimationColor::setFactor(float newFactor) { factor = newFactor; }

void AnimationColor::update() {
    factor = factor + UPDATE_RATE * updateSpeed;
    if (factor > 1.f) factor = 1.f;
}

void AnimationColor::setUpdateRate(float newSpeed) { updateSpeed = newSpeed; }

Color AnimationColor::getCurrentColor() {
    currentColor = ColorLerp(baseColor, targetColor, factor);
    return currentColor;
};

bool AnimationColor::isCompleted() { return abs(factor - 1.f) < 1e-6; }

float AnimationColor::getFactor() { return factor; }

Color AnimationColor::getBaseColor() { return baseColor; }

Color AnimationColor::getTargetColor() { return targetColor; }

void AnimationColor::makeFinish() { setFactor(1.0f); }