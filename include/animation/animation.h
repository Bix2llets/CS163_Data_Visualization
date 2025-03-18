#pragma once
#include <iostream>

#include "GUIObject.h"
#include "raylib.h"
#include "raymath.h"
class Animation : public GUIObject {
   private:
    static float rate;
    Vector2 targetedPosition;

   public:
    Animation(float x, float y)
        : GUIObject(x, y),
          targetedPosition{x, y} {};
    void update();
    void setTargetedPosition(Vector2 target);
    Vector2 getTargetedPosition();
    bool isCompleted() const;
    static void setUpdateRate(float newRate);
    void makeFinish();

    virtual void render();
};