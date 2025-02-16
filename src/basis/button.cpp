#include "button.h"
#include "utility.h"
#include <iostream>
void Button::render() {
    Rectangle rect{position.x, position.y, dimension.x, dimension.y};
    if (isHovered())
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, hoverColor);
    else
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, backgroundColor);
    TextUtility::renderText(text, {position.x + dimension.x / 2, position.y + dimension.y / 2}, TextUtility::fontInter, textColor, fontSize, SPACING);
    DrawRectangleLinesEx(rect, 3, textColor);
}

void Button::setText(std::string newText) { text = newText; }

bool Button::isHovered() const {
    Vector2 mousePosition = GetMousePosition();
    // std::cerr << mousePosition.x << " " << mousePosition.y << "\n";
    if (mousePosition.x < position.x) return false;
    if (mousePosition.x > position.x + dimension.x) return false;
    if (mousePosition.y < position.y) return false;
    if (mousePosition.y > position.y + dimension.y) return false;
    // std::cerr << "Inside box\n";
    return true;
}

bool Button::isPressed() const {
    if (!isHovered()) return false;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return true;
    return false;
}