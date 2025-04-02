#include "button.h"

#include <iostream>

#include "utility.h"
void Button::render() {
    if (!enabled) return;

    Color borderColor;
    Color backgroundColor;
    Color textColor;
    float innerOffset;
    float outerOffset;
    if (isHovered()) {
        borderColor = PALETTE->borderHighlight;
        backgroundColor = PALETTE->backgroundHighlight;
        textColor = PALETTE->textHighlight;
    } else {
        borderColor = PALETTE->borderNormal;
        backgroundColor = PALETTE->backgroundNormal;
        textColor = PALETTE->textNormal;
    }

    Rectangle renderInfo = {position.x - BORDER_OFFSET, position.y - BORDER_OFFSET,
                            dimension.x + 2 * (BORDER_OFFSET) ,
                            dimension.y + 2 * (BORDER_OFFSET)};

    DrawRectangleRounded(renderInfo, 0.5f, 100, backgroundColor);
    // DrawRectangle(renderInfo.x, renderInfo.y, renderInfo.width,
                //   renderInfo.height, backgroundColor);

    DrawRectangleRoundedLinesEx(renderInfo, 0.5f, 0, BORDER_OFFSET * 2, borderColor);
    DrawUtility::drawText(
        text, {position.x + dimension.x / 2, position.y + dimension.y / 2},
        DrawUtility::inter20, textColor, DrawUtility::NORMAL_SIZE,
        DrawUtility::SPACING, VerticalAlignment::CENTERED,
        HorizontalAlignment::CENTERED);
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
