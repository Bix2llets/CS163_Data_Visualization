#include "button.h"

#include <iostream>
void Button::render() {
    Rectangle rect{position.x, position.y, dimension.x, dimension.y};
    if (isHovered())
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, hoverColor);
    else
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, backgroundColor);

    Vector2 textStart{rect.x + rect.width / 2, rect.y + rect.height / 2};
    Vector2 textDimension =
        MeasureTextEx(font, text.c_str(), fontSize, SPACING);
    textDimension = Vector2Scale(textDimension, 0.5f);
    textStart = Vector2Subtract(textStart, textDimension);
    DrawTextEx(font, text.c_str(), textStart, fontSize, SPACING, textColor);
}

void Button::setText(std::string newText) { text = newText; }

bool Button::isHovered() const {
    Vector2 mousePosition = GetMousePosition();
    // std::cerr << mousePosition.x << " " << mousePosition.y << "\n";
    if (mousePosition.x < position.x) return false;
    if (mousePosition.x > position.x + dimension.x) return false;
    if (mousePosition.y < position.y) return false;
    if (mousePosition.y > position.x + dimension.y) return false;
    // std::cerr << "Inside box\n";
    return true;
}

bool Button::isPressed() const {
    if (!isHovered()) return false;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return true;
    return false;
}