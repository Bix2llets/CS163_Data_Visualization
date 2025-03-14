#include "textbox.h"

#include <iostream>
void TextBox::render() {
    update();
    DrawRectangleV(position, Vector2{width, height},
                   PALETTE.backgroundHighlight);
    Vector2 textPosition = position;
    textPosition.y += height / 2;
    textPosition.x += LEFT_MARGIN;
    Color textColor, groundColor, borderColor;

    std::string textRender = text;
    if (isFocusedOn) {
        textColor = PALETTE.textHighlight;
        textRender += '_';
        groundColor = PALETTE.backgroundHighlight;
        borderColor = PALETTE.borderHighlight;
    } else {
        textColor = PALETTE.textNormal;
        groundColor = PALETTE.backgroundNormal;
        borderColor = PALETTE.borderNormal;
    }
    DrawRectangle(position.x, position.y, width, height, groundColor);
    DrawRectangleLinesEx({position.x, position.y, width, height}, 3, borderColor);
    DrawUtility::drawText(textRender, textPosition, DrawUtility::inter20,
                          textColor, DrawUtility::NORMAL_SIZE,
                          DrawUtility::SPACING,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::LEFT);
}
void TextBox::recordKeyboard() {
    if (!isFocusedOn) return;
    if (IsKeyPressed(KEY_BACKSPACE)) {
        text = text.substr(0, text.length() - 1);
        // std::cerr << "Erased " << text << "\n";
        return;
    }
    bool isCaptialized = false;
    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
        isCaptialized = true;
    int keyNum = GetKeyPressed();
    char chr = '\0';
    if (KEY_A <= keyNum && keyNum <= KEY_Z) {
        if (isCaptialized)
            chr = keyNum - KEY_A + 'A';
        else
            chr = keyNum - KEY_A + 'a';
    } else if (KEY_ZERO <= keyNum && keyNum <= KEY_NINE)
        chr = keyNum - KEY_ZERO + '0';

    if (chr != '\0' && text.length() <= 30) text = text + chr;
    // std::cerr << chr << " " << text << "\n";
}
void TextBox::recordFocus() {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;
    Vector2 mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition,
                               {position.x, position.y, width, height}))
        isFocusedOn = true;
    else
        isFocusedOn = false;
}

void TextBox::deFocus() { isFocusedOn = false; }
std::string TextBox::getText() { return text; }

void TextBox::update() {
    recordFocus();
    recordKeyboard();
}

std::pair<bool, int> TextBox::getValue() {
    if (text.size() == 0) return {0, 0};
    for (char chr: text) if (chr < '0' || '9' < chr) return {0, 0};
    return {1, std::stoi(text)};
}