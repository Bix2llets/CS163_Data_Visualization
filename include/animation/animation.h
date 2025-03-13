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
    void update(float rate);
    void setTargetedPosition(Vector2 target);
    Vector2 getTargetedPosition();
    Vector2 getPosition();
    void setPosition(Vector2 newPosition);
    bool isCompleted() const;
    void setUpdateRate(float newRate);
    double bezier(double t);
    bool displace(double currentTime, double TRANS_TIME);
    virtual void render();
};