#include "textbox.h"

#include <iostream>
void TextBox::render() {
    recordFocus();
    recordKeyboard();
    DrawRectangleV(position, Vector2{width, height},
                   PALETTE.backgroundHighlight);
    Vector2 textPosition = position;
    textPosition.y += height / 2;
    textPosition.x += LEFT_MARGIN;
    Color textColor, groundColor;

    std::string textRender = text;
    if (isFocusedOn) {
        textColor = PALETTE.textHighlight;
        textRender += '_';
        groundColor = PALETTE.backgroundHighlight;
    } else {
        textColor = PALETTE.textNormal;
        groundColor = PALETTE.backgroundNormal;
    }
    if (PALETTE.renderBorder) DrawRectangleLinesEx({position.x, position.y, width, height}, 3, PALETTE.border);
    TextUtility::drawText(textRender, textPosition, TextUtility::inter20,
                          textColor, TextUtility::NORMAL_SIZE,
                          TextUtility::SPACING,
                          TextUtility::VerticalAlignment::CENTERED,
                          TextUtility::HorizontalAlignment::LEFT);
}
void TextBox::recordKeyboard() {
    if (!isFocusedOn) return;
    if (IsKeyPressed(KEY_BACKSPACE)) {
        text = text.substr(0, text.length() - 1);
        std::cerr << "Erased " << text << "\n";
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
    std::cerr << chr << " " << text << "\n";
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