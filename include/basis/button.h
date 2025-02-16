#pragma once
#include <string>

#include "GUIObject.h"
#include "raylib.h"
#include "raymath.h"

class Button : public GUIObject {
    int fontSize;
    const static int SPACING = 1;
    Vector2 dimension;
    Color textColor, backgroundColor;
    std::string text;
    Color hoverColor;

   public:
    Button(Vector2 position, Vector2 dimension, std::string text = "",
           int fontSize = 12, Color textColor = WHITE,
           Color backgroundColor = BLACK, Color hoverColor = GREEN)
        : GUIObject(position),
          dimension{dimension},
          text{text},
          fontSize{fontSize},
          textColor{textColor},
          backgroundColor{backgroundColor},
          hoverColor{hoverColor} {
    };

    Button(Rectangle rectangle, std::string text = "", int fontSize = 12,
           Color textColor = WHITE, Color backgroundColor = BLACK,
           Color hoverColor = GREEN)
        : Button{Vector2{rectangle.x, rectangle.y},
                 Vector2{rectangle.width, rectangle.height},
                 text,
                 fontSize,
                 textColor,
                 backgroundColor,
                 hoverColor} {};

    Button(float x, float y, float width, float height, std::string text = "",
           int fontSize = 12, Color textColor = WHITE,
           Color backgroundColor = BLACK, Color hoverColor = GREEN)
        : Button{Vector2{x, y}, Vector2{width, height}, text,      fontSize,
                 textColor,     backgroundColor,        hoverColor} {};

    Vector2 getDimension() const { return dimension; }

    virtual void render();

    void setText(std::string newText);

    bool isPressed() const;
    bool isHovered() const;
};
