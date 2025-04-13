#pragma once
#include <string>

#include "raylib.h"
#include "raymath.h"
#include <vector>
enum class VerticalAlignment { TOP, CENTERED, BOTTOM };
enum class HorizontalAlignment { LEFT, CENTERED, RIGHT };
Vector2 randomPosition();

bool isStrNum(std::string str);
namespace Utility {
extern Font inter12;
extern Font inter16;
extern Font inter20;
extern Font inter30;
extern Font jbm20;
extern Font noto;
extern const int NORMAL_SIZE;
extern const int SPACING;

extern int highlightingRow; // Left for backward compatibility, but not used anymore
extern Texture2D diceTexture[6], dice, pause, play, prev, next, forward,
    backward, expand, collapse;

void init();
void drawText(std::string text, Vector2 position, Font font, Color textColor,
              int fontSize, int spacing, VerticalAlignment verticalAlign,
              HorizontalAlignment horizontalAlign);

void drawEdge(Vector2 beginPostion, Vector2 endPosition, Color color);

// Removed vector declarations as they've been moved to their respective classes

std::string GenerateRandomText(int length);
int GenerateRandomNum(int length);
void GenerateRandomText(char *text);
void GenerateRandomNum(char *text);

// Removed DrawTextTrie and DrawTextHash function declarations
}  // namespace Utility
