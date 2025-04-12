#pragma once
#include <string>

#include "raylib.h"
#include "raymath.h"
enum class VerticalAlignment { TOP, CENTERED, BOTTOM };
enum class HorizontalAlignment { LEFT, CENTERED, RIGHT };
Vector2 randomPosition();

bool isStrNum(std::string str);
namespace Utility {
extern Font inter20;
extern Font inter16;
extern Font inter12;
extern Font jbm20;
extern Font noto;
extern const int NORMAL_SIZE;
extern const int SPACING;
void init();
void drawText(std::string text, Vector2 position, Font font, Color textColor,
              int fontSize, int spacing, VerticalAlignment verticalAlign,
              HorizontalAlignment horizontalAlign);

void drawEdge(Vector2 beginPostion, Vector2 endPosition, Color color);
}  // namespace Utility
