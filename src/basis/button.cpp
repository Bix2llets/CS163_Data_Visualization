#include "button.h"
#include "utility.h"
#include <iostream>
void Button::render() {
    if (!enabled) return;
    Rectangle rect{position.x - 1, position.y - 1, dimension.x + 2, dimension.y + 2};
    if (isHovered())
    {

        DrawRectangle(rect.x, rect.y, rect.width, rect.height, PALETTE.backgroundHighlight);
        DrawUtility::drawText(text, {position.x + dimension.x / 2, position.y + dimension.y / 2}, DrawUtility::inter20, PALETTE.textHighlight, fontSize, SPACING, VerticalAlignment::CENTERED, HorizontalAlignment::CENTERED);
        DrawRectangleLinesEx(rect, 2, PALETTE.borderHighlight);
    }
    else
    
    {
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, PALETTE.backgroundNormal);
        DrawUtility::drawText(text, {position.x + dimension.x / 2, position.y + dimension.y / 2}, DrawUtility::inter20, PALETTE.textNormal, fontSize, SPACING, VerticalAlignment::CENTERED, HorizontalAlignment::CENTERED);
        DrawRectangleLinesEx(rect, 2, PALETTE.borderNormal);
    }
}

void Button::setText(std::string newText) { text = newText; }

bool Button::isHovered() const {
    Vector2 mousePosition = GetMousePosition();
    // std::cerr << mousePosition.x << " " << mousePosition.y << "\n";
    if (mousePosition.x <= position.x) return false;
    if (mousePosition.x >= position.x + dimension.x) return false;
    if (mousePosition.y <= position.y) return false;
    if (mousePosition.y >= position.y + dimension.y) return false;
    // std::cerr << "Inside box\n";
    return true;
}

bool Button::isPressed() const {
    if (!enabled) return false;
    if (!isHovered()) return false;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return true;
    return false;
}

bool Button::isEnabled() {
    return enabled;
}

void Button::enable() {
    enabled = true;
}

void Button::disable() {
    enabled = false;
}

void Button::toggleEnabled() {
    enabled = !enabled;
}