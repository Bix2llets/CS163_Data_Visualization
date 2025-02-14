#include "button.h"

void Button::render() {
    Rectangle rect{position.x, position.y, dimension.x, dimension.y};
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, backgroundColor);

    Vector2 textStart{rect.x + rect.width / 2, rect.y + rect.height / 2};
    Vector2 textDimension =
        MeasureTextEx(font, text.c_str(), FONT_SIZE, SPACING);
    textDimension = Vector2Scale(textDimension, 0.5f);
    textStart = Vector2Subtract(textStart, textDimension);
    DrawTextEx(font, text.c_str(), textStart, FONT_SIZE, SPACING, textColor);
}