#include "utility.h"
namespace TextUtility {
const int SPACING = 1;
const int NORMAL_SIZE = 20;
Font inter20;
void drawText(std::string text, Vector2 position, Font font,
                      Color textColor, int fontSize, int spacing, VerticalAlignment verticalAlign, HorizontalAlignment horizontalAlign) {
    Vector2 textDimension =
        MeasureTextEx(font, text.c_str(), fontSize, spacing);
    
    if (verticalAlign == VerticalAlignment::CENTERED) position.y -= 0.5 * textDimension.y;
    if (verticalAlign == VerticalAlignment::TOP) position.y -= textDimension.y;

    if (horizontalAlign == HorizontalAlignment::CENTERED) position.x -= 0.5 * textDimension.x;
    if (horizontalAlign == HorizontalAlignment::RIGHT) position.x -= textDimension.x;
    DrawTextEx(font, text.c_str(), position, fontSize, spacing, textColor);
}

void init() {
    {
        inter20 = LoadFontEx("assets/Inter-Black.ttf", 20, NULL, 0);
    }
}

void drawLeftAlginedText(std::string text, Vector2 position, Font font,
                         Color color, int fontSize, int spacing) {
    DrawTextEx(font, text.c_str(), position, fontSize, spacing, color);
}
}  // namespace TextUtility