#pragma once
#include "raylib.h"
class GUIObject {
   protected:
    Vector2 position; 

   public:
    GUIObject(Vector2 position) : position{position} {};
    GUIObject(float x, float y) : position{Vector2{x, y}} {};

    void setPosition(Vector2 _position);
    void setPosition(float x, float y);

    Vector2 getPosition() const { return position; }

    virtual void render() = 0;

};