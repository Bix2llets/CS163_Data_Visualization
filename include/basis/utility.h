#ifndef UTILITY_H
#define UTILITY_H
#include <string>

#include "raylib.h"
#include "raymath.h"
namespace TextUtility {
extern Font fontInter;
const int NORMAL_SIZE = 14;
const int SPACING = 1;
void init();
void renderText(std::string text, Vector2 position, Font font, Color textColor,
                int fontSize, int spacing);
}  // namespace TextUtility
#endif