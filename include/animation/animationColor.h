#include "raylib.h"
#include "math.h"
#pragma once
class AnimationColor {
   protected:
    Color baseColor;
    Color targetColor;
    Color currentColor;
    float factor;
    float UPDATE_RATE;
    float updateSpeed;

   public:
    AnimationColor(float updateSpeed = 1);
    AnimationColor(Color baseColor, Color targetColor, float updateSpeed = 1);
    void setTargetColor(Color color);
    void setBaseColor(Color color);
    void setCurrentColor(Color color);
    void setFactor(float newFactor);
    void setUpdateRate(float newSpeed);
    void update();
    
    Color getBaseColor();
    Color getTargetColor();
    
    bool isCompleted();
    int getAnimationRate();
    Color getCurrentColor();

    void makeFinish();
    float getFactor();
};