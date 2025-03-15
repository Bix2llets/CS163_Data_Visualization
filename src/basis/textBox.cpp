#include "textbox.h"
void TextBox::render() {
    if (font == nullptr)
    {
        std::cerr << "Null font, unexpected\n";
        return;

    } 
    float renderWidth = width;
    float renderHeight = height;
    Vector2 textDimension = MeasureTextEx(*font, text.c_str(), DrawUtility::NORMAL_SIZE, DrawUtility::SPACING);

    renderWidth = std::max(textDimension.x + OFFSET * 2, renderWidth);

    Color backgroundColor;
    Color textColor;
    Color borderColor;
    if (isHighlighted) {
        backgroundColor = color.backgroundHighlight;
        textColor = color.textHighlight;
        borderColor = color.borderHighlight;
    }
    else {
        backgroundColor = color.backgroundNormal;
        textColor = color.textNormal;
        borderColor = color.borderNormal;
    }
    Rectangle drawInfo{position.x - 1, position.y - 1, renderWidth + 2, renderHeight + 2};
    DrawRectangle(drawInfo.x, drawInfo.y, drawInfo.width, drawInfo.height, backgroundColor);
    DrawRectangleLinesEx(drawInfo, 2, borderColor);
    DrawUtility::drawText(text, {position.x + OFFSET, position.y + textDimension.y / 2}, *font, textColor, DrawUtility::NORMAL_SIZE, DrawUtility::SPACING, VerticalAlignment::CENTERED, HorizontalAlignment::LEFT);
}  

void TextBox::setText(std::string newText) {
    text = newText;
}

void TextBox::setFont(Font* newFont) {
    font = newFont;
}

void TextBox::setHighlight(bool newState) {
    isHighlighted = newState;
}