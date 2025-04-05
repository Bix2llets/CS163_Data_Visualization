#pragma once
#include <iostream>

#include "GUIObject.h"
#include "raylib.h"
#include "raymath.h"
class Animation : public GUIObject {
   private:
    static float rate;
    Vector2 targetedPosition;
    float alpha, hashAlpha;

   public:
    Animation(float x, float y)
        : GUIObject(x, y),
          targetedPosition{x, y},
          alpha(255.f),
          hashAlpha(0.f) {};
    void update();
    void update(float rate);
    void setTargetedPosition(Vector2 target);
    Vector2 getTargetedPosition();
    Vector2 getPosition();
    void setPosition(Vector2 newPosition);
    bool isCompleted() const;
    static void setUpdateRate(float newRate);
    // * For linear motion
    //void update();

    // * For customized motion
    double bezier(double t);
    bool displace(double currentTime, double TRANS_TIME);
    bool fadeEffect(double currentTime, double TRANS_TIME);
    bool updateHashAlpha(double currentTime, double TRANS_TIME);
    void makeFinish();
    virtual void render();
    float getAlpha() { return alpha; }
    float getHashAlpha() { return 255.f - hashAlpha; }
    void setHashAlpha(float _alpha) { hashAlpha = _alpha; }
};        