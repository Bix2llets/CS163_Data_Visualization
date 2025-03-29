#include "insertBox.hpp"
#include <mLib/Utility.hpp>

std::string InsertBox::handleInput() {
    if (IsKeyPressed(KEY_ENTER) || submitButton.isPressed()) return form.getText();
    if (RanButton.isPressed()) {
        if (mode == 0) {
            form.setText(std::to_string(mLib::GenerateRandomNum(maxSize)));
        } else {
            form.setText(mLib::GenerateRandomText(maxSize));
        }
    }
    return "";
}