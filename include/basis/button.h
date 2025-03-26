#pragma once
#include <string>

#include "GUIObject.h"
#include "animation.h"
#include "animationColor.h"
#include "colorPalette.h"
#include "raylib.h"
#include "raymath.h"
#include "toggleable.h"
class Button : public GUIObject, public Toggleable {
   protected:
    Vector2 dimension;
   private:
    int fontSize;
    constexpr static float TEXT_OFFSET = 5;
    constexpr static float BORDER_OFFSET = 1;
    ColorSet PALETTE;
    std::string text;

    AnimationColor edgeColor;

   public:
    Button(Vector2 position, Vector2 dimension, std::string text = "",
           int fontSize = 20, ColorSet palette = COLOR_SET_1)
        : GUIObject(position),
          dimension{dimension},
          text{text},
          fontSize{fontSize},
          PALETTE{palette},
          edgeColor{},
          Toggleable() {};

    Button(Rectangle rectangle = {0, 0, 0, 0}, std::string text = "", int fontSize = 20,
           ColorSet palette = COLOR_SET_1)
        : Button{Vector2{rectangle.x, rectangle.y},
                 Vector2{rectangle.width, rectangle.height}, text, fontSize,
                 palette} {};

    Button(float x, float y, float width, float height, std::string text = "",
           int fontSize = 20, ColorSet palette = COLOR_SET_1)
        : Button{Vector2{x, y}, Vector2{width, height}, text, fontSize,
                 palette} {};

    Vector2 getDimension() const { return dimension; }

    virtual void render();

    void setText(std::string newText);

    bool isPressed() const;
    bool isHovered() const;
};
