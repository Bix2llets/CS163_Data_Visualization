#include "mForm.h"

#include <iostream>

void mForm::recordKeyboard() {
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
    if (newText.size() > maxSize) return;
    if ('0' <= chr && chr <= '9' && mode == 1) return;
    if ((('a' <= chr && chr <= 'z') || ('A' <= chr && chr <= 'Z')) && mode == 0)
        return;
    if (mode == 1) chr = toupper(chr);
    Vector2 newDimension =
       MeasureTextEx(Utility::inter16, newText.c_str(),
                      16, Utility::SPACING);

    if (newDimension.x > width - LEFT_MARGIN - RIGHT_MARGIN) return;

    text = text + chr;
}