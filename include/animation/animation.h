#include <iostream>

#include "GUIObject.h"
#include "raylib.h"
#include "raymath.h"
class Animation : public GUIObject {
   private:
    const float DELTA_TIME = 1.0 / 24;
    const float BASE_VELOCITY = 1;
    float velocityCoefficient;
    Vector2 targetedPosition;

   public:
    Animation(float x, float y, float coefficient = 1)
        : velocityCoefficient{coefficient},
          GUIObject(x, y),
          targetedPosition{x, y} {};
    void update();
    void setTargetedPosition(Vector2 target);

    bool isCompleted() const;
    virtual void render();
};