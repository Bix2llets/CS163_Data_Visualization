#include "textbox.h"

void TextBox::render() {
    if (isFocusedOn) {
        DrawRectangleV(position, Vector2{width, height}, PALETTE.backgroundHighlight);
        
        Vector2 textDimension = MeasureTextEx(TextUtility::inter20, text.c_str(), TextUtility::NORMAL_SIZE, TextUtility::SPACING);

        
    }
}
void TextBox::recordKeyboard() {}
void TextBox::recordFocus() {}