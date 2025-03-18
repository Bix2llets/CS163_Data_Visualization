#include "raylib.h"
#include "math.h"
#pragma once
class AnimationColor {
   protected:
    Color baseColor;
    Color targetColor;
    Color currentColor;
    float factor;
    const static float BASE_RATE;
    static float updateSpeed;

   public:
    AnimationColor();
    AnimationColor(Color baseColor, Color targetColor);
    void setTargetColor(Color color);
    void setBaseColor(Color color);
    void setCurrentColor(Color color);
    void setFactor(float newFactor);
    static void setUpdateRate(float newSpeed);
    void update();
    
    Color getBaseColor();
    Color getTargetColor();
    
    bool isCompleted();
    int getAnimationRate();
    Color getCurrentColor();

    void makeFinish();
    float getFactor();
};