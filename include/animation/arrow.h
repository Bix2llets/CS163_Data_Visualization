#pragma once
#include "GUIObject.h"
#include "animation.h"
#include "utility.h"
class AnimationEdge{
   private:
    Animation beginPosition;
    Animation endPosition;
    bool isHighlighted;
    Color normalColor, highlightColor;

   public:
    AnimationEdge(Vector2 beginPos, Vector2 endPos, Color normalColor,
                   Color highlightColor, float velocity = 1)
        : beginPosition{beginPos.x, beginPos.y, velocity},
          endPosition{endPos.x, endPos.y, velocity},
          normalColor{normalColor},
          highlightColor{highlightColor},
          isHighlighted{false} {};
    
    void render();

    void update();

    void setAnimationBeginPosition(Vector2 target);
    void setAnimationEndPosition(Vector2 target);
    void setBeginPosition(Vector2 target);
    void setEndPosition(Vector2 target);
    void setHighlight(bool highlight);
    void setVelocity(float velo);
    bool isCompleted();

    Vector2 getBeginPosition();
    Vector2 getEndPosition();
    Vector2 getTargetedBeginPosition();
    Vector2 getTargetedEndPosition();
};