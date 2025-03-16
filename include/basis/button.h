#pragma once
#include <string>

#include "GUIObject.h"
#include "animation.h"
#include "animationColor.h"
#include "colorPalette.h"
#include "raylib.h"
#include "raymath.h"
class Button : public GUIObject {
   protected:
    bool enabled;
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
           int fontSize = 20, ColorSet palette = DEF_SET)
        : GUIObject(position),
          dimension{dimension},
          text{text},
          fontSize{fontSize},
          PALETTE{palette},
          edgeColor{},
          enabled{true} {};

    Button(Rectangle rectangle = {0, 0, 0, 0}, std::string text = "", int fontSize = 20,
           ColorSet palette = DEF_SET)
        : Button{Vector2{rectangle.x, rectangle.y},
                 Vector2{rectangle.width, rectangle.height}, text, fontSize,
                 palette} {};

    Button(float x, float y, float width, float height, std::string text = "",
           int fontSize = 20, ColorSet palette = DEF_SET)
        : Button{Vector2{x, y}, Vector2{width, height}, text, fontSize,
                 palette} {};

    Vector2 getDimension() const { return dimension; }

    virtual void render();

    void setText(std::string newText);

    bool isPressed() const;
    bool isHovered() const;

    bool isEnabled();
    void toggleEnabled();
    void enable();
    void disable();
};
