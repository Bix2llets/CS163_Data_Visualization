#pragma once
#include <iostream>

#include "GUIObject.h"
#include "raylib.h"
#include "raymath.h"
class Animation : public GUIObject {
   private:
    float velocity;
    Vector2 targetedPosition;

   public:
    Animation(float x, float y, float velocity = 1)
        : velocity{velocity},
          GUIObject(x, y),
          targetedPosition{x, y} {};
    void update();
    void setTargetedPosition(Vector2 target);
    Vector2 getTargetedPosition();
    bool isCompleted() const;
    void setVelocity(float velo);

    virtual void render();
};