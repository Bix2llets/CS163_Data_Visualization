#include "form.h"

#include <iostream>
void Form::render() {
    if (!enabled) return;
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
    Rectangle drawInfo = {position.x - BORDER_OFFSET, position.y - BORDER_OFFSET, width + 2 * BORDER_OFFSET, height + 2 * BORDER_OFFSET};
    DrawRectangle(drawInfo.x, drawInfo.y, drawInfo.width, drawInfo.height, groundColor);
    DrawRectangleLinesEx(drawInfo, 2 * BORDER_OFFSET, borderColor);
    DrawUtility::drawText(textRender, textPosition, DrawUtility::inter20,
                          textColor, DrawUtility::NORMAL_SIZE,
                          DrawUtility::SPACING,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::LEFT);
}
void Form::recordKeyboard() {
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
    else if (keyNum == KEY_SPACE)
        chr = ' ';

    if (chr == '\0') return;
    std::string newText = text + chr;
    Vector2 newDimension = MeasureTextEx(DrawUtility::inter20, newText.c_str(), DrawUtility::NORMAL_SIZE, DrawUtility::SPACING); 

    if (newDimension.x > width - LEFT_MARGIN - RIGHT_MARGIN) return;
    
    text = text + chr;
    // std::cerr << chr << " " << text << "\n";
}
void Form::recordFocus() {
    if (!enabled) {isFocusedOn = false; return;}
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return;
    Vector2 mousePosition = GetMousePosition();
    if (CheckCollisionPointRec(mousePosition,
                               {position.x + 1, position.y + 1, width - 1, height - 1}))
        isFocusedOn = true;
    else
        isFocusedOn = false;
}

void Form::deFocus() { isFocusedOn = false; }
std::string Form::getText() { return text; }

void Form::update() {
    recordFocus();
    recordKeyboard();
}

std::pair<bool, int> Form::getValue() {
    if (text.size() == 0) return {0, 0};
    for (char chr: text) if (chr < '0' || '9' < chr) return {0, 0};
    return {1, std::stoi(text)};
}
