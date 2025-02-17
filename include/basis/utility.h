#pragma once
#include <string>

#include "raylib.h"
#include "raymath.h"
namespace TextUtility {
enum class VerticalAlignment {
    TOP, 
    CENTERED,
    BOTTOM
};
enum class HorizontalAlignment {
    LEFT, 
    CENTERED,
    RIGHT
};
extern Font inter20;
extern const int NORMAL_SIZE;
extern const int SPACING ;
void init();
void drawText(std::string text, Vector2 position, Font font, Color textColor,
                int fontSize, int spacing, VerticalAlignment verticalAlign, HorizontalAlignment horizontalAlign);

}  // namespace TextUtility