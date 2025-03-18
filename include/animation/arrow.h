#pragma once
#include "GUIObject.h"
#include "animation.h"
#include "animationColor.h"
#include "utility.h"
class AnimationEdge{
   private:
    Animation beginPosition;
    Animation endPosition;
    bool isHighlighted;
    float factor;
    public:
    
    AnimationColor currentColor;
    AnimationEdge(Vector2 beginPos, Vector2 endPos, AnimationColor currentColor, float newFac = 1);
    
    void render();

    void update();

    void updateMotion();
    void updateColor();
    
    void setMotionBeginPosition(Vector2 target);
    void setMotionEndPosition(Vector2 target);

    void setBeginPosition(Vector2 target);
    void setEndPosition(Vector2 target);

    void setColor(AnimationColor newColor);
    void setBaseColor(Color color);
    void setTargetColor(Color color);
    void setFactor(float factor);
    
    bool isMotionCompleted();
    bool isColorCompleted();

    void makeFinish();

    Vector2 getBeginPosition();
    Vector2 getEndPosition();
    Vector2 getTargetedBeginPosition();
    Vector2 getTargetedEndPosition();
};