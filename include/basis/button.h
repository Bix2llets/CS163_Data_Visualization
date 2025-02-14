#pragma once
#include <string>

#include "GUIObject.h"
#include "raylib.h"
#include "raymath.h"

class Button : public GUIObject {
    Font font;
    const static int FONT_SIZE = 12;
    const static int SPACING = 1;
    Vector2 dimension;
    Color textColor, backgroundColor;
    std::string text;

   public:
    Button(Vector2 position, Vector2 dimension, std::string text = "", Color textColor = WHITE,
           Color backgroundColor = BLACK)
        : GUIObject(position), dimension{dimension} {
        font = LoadFont("../assets/Inter-black.ttf");
    };

    Button(Rectangle rectangle, std::string text = "", Color textColor = WHITE,
           Color backgroundColor = BLACK)
        : GUIObject{Vector2{rectangle.x, rectangle.y}},
          dimension{Vector2{rectangle.width, rectangle.height}},
          textColor{textColor},
          backgroundColor{backgroundColor} {};

    Button(float x, float y, float width, float height, std::string text = "", Color textColor = WHITE, Color backgroundColor = BLACK)
        : GUIObject{Vector2{x, y}},
          dimension{Vector2{width, height}},
          textColor{textColor},
          backgroundColor{backgroundColor} {};

    Vector2 getDimension() const { return dimension; }

    virtual void render();

    void setText(std::string newText);
};
