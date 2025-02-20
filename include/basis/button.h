#pragma once
#include <string>

#include "GUIObject.h"
#include "colorPalette.h"
#include "raylib.h"
#include "raymath.h"
#include "animation.h"
#include "animationColor.h"
class Button : public GUIObject {
    int fontSize;
    const static int SPACING = 1;
    Vector2 dimension;
    const ColorPalette::ColorSet PALETTE;
    std::string text;

    AnimationColor edgeColor;
   public:
    Button(Vector2 position, Vector2 dimension, std::string text = "",
           int fontSize = 20,
           ColorPalette::ColorSet palette =
               ColorPalette::ColorSet{WHITE, WHITE, GRAY, GREEN, false, BLACK})
        : GUIObject(position),
          dimension{dimension},
          text{text},
          fontSize{fontSize},
          PALETTE{palette}, edgeColor{}{};

    Button(Rectangle rectangle, std::string text = "", int fontSize = 20,
           ColorPalette::ColorSet palette =
               ColorPalette::ColorSet{WHITE, WHITE, GRAY, GREEN, false, BLACK})
        : Button{Vector2{rectangle.x, rectangle.y},
                 Vector2{rectangle.width, rectangle.height}, text, fontSize,
                 palette} {};

    Button(float x, float y, float width, float height, std::string text = "",
           int fontSize = 20,
           ColorPalette::ColorSet palette =
               ColorPalette::ColorSet{WHITE, WHITE, GRAY, GREEN, false, BLACK})
        : Button{Vector2{x, y}, Vector2{width, height}, text, fontSize,
                 palette} {};

    Vector2 getDimension() const { return dimension; }

    virtual void render();

    void setText(std::string newText);

    bool isPressed() const;
    bool isHovered() const;
};
