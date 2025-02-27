#pragma once
#include <string>

#include "raylib.h"
#include "raymath.h"
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
namespace DrawUtility {
extern Font inter20;
extern const int NORMAL_SIZE;
extern const int SPACING ;
void init();
void drawText(std::string text, Vector2 position, Font font, Color textColor,
                int fontSize, int spacing, VerticalAlignment verticalAlign, HorizontalAlignment horizontalAlign);

void drawEdge(Vector2 beginPostion, Vector2 endPosition, Color color);

extern const Color EDGE_NORMAL;
extern const Color EDGE_HIGHLIGHTED;
extern const Color TEXT_COLOR;

}  // namespace TextUtility