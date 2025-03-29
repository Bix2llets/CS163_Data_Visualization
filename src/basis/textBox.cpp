#include "textbox.h"
void TextBox::render() {
    if (!enabled) return;
    if (font == nullptr) {
        std::cerr << "Null font, unexpected\n";
        return;
    }
    float renderWidth = width;
    float renderHeight = height;
    Vector2 textDimension = MeasureTextEx(
        *font, text.c_str(), DrawUtility::NORMAL_SIZE, DrawUtility::SPACING);

    renderWidth = std::max(textDimension.x + OFFSET * 2, renderWidth);

    Color backgroundColor;
    Color textColor;
    Color borderColor;
    if (isHighlighted) {
        backgroundColor = color->backgroundHighlight;
        textColor = color->textHighlight;
        borderColor = color->borderHighlight;
    } else {
        backgroundColor = color->backgroundNormal;
        textColor = color->textNormal;
        borderColor = color->borderNormal;
    }
    Rectangle drawInfo{position.x - BORDER_OFFSET, position.y - BORDER_OFFSET,
                       renderWidth + 2 * BORDER_OFFSET,
                       renderHeight + 2 * BORDER_OFFSET};
    DrawRectangle(drawInfo.x, drawInfo.y, drawInfo.width, drawInfo.height,
                  backgroundColor);
    DrawRectangleLinesEx(drawInfo, 2 * BORDER_OFFSET, borderColor);

    Vector2 textPosition;
    switch (verticalAlign) {
        case VerticalAlignment::CENTERED:
            textPosition.y = position.y + height / 2;
            break;
        case VerticalAlignment::BOTTOM:
            textPosition.y = position.y + height - OFFSET;
            break;
        case VerticalAlignment::TOP:
            textPosition.y = position.y + OFFSET;
            break;
    }

    switch (horizontalAlign) {
        case HorizontalAlignment::CENTERED:
            textPosition.x = position.x + width / 2;
            break;
        case HorizontalAlignment::LEFT:
            textPosition.x = position.x + OFFSET;
            break;
        case HorizontalAlignment::RIGHT:
            textPosition.x = position.x + width - OFFSET;
            break;
    }
    DrawUtility::drawText(text, textPosition, *font, textColor,
                          DrawUtility::NORMAL_SIZE, DrawUtility::SPACING,
                          verticalAlign, horizontalAlign);
                          std::cout << "rendering text box\n";
}

void TextBox::setText(std::string newText) { text = newText; }

void TextBox::setFont(Font* newFont) { font = newFont; }

void TextBox::setHighlight(bool newState) { isHighlighted = newState; }