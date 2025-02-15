#include "utility.h"
namespace TextUtility {
Font fontInter;
void renderText(std::string text, Vector2 position, Font font, Color textColor,
                int fontSize, int spacing) {
    Vector2 textDimension =
        MeasureTextEx(font, text.c_str(), fontSize, spacing);
    position = Vector2Add(position, Vector2Scale(textDimension, -0.5));
    DrawTextEx(font, text.c_str(), position, NORMAL_SIZE, SPACING, textColor);
}

void init() {
    {
        fontInter = LoadFont("assets/Inter-Black.ttf");
    }
}
}  // namespace Utility