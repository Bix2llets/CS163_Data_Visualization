#pragma once
#include <iostream>

#include "GUIObject.h"
#include "raylib.h"
#include "raymath.h"
class Animation : public GUIObject {
   private:
    float rate;
    Vector2 targetedPosition;

   public:
    Animation(float x, float y, float rate = 1)
        : rate{rate},
          GUIObject(x, y),
          targetedPosition{x, y} {};
    void update();
    void setTargetedPosition(Vector2 target);
    Vector2 getTargetedPosition();
    bool isCompleted() const;
    void setUpdateRate(float newRate);
    void makeFinish();

    virtual void render();
};