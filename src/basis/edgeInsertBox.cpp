#include "edgeInsertBox.hpp"
#include <mLib/Utility.hpp>

std::vector<std::string> edgeInsertBox::handleInput() {
    if (IsKeyPressed(KEY_ENTER) || submitButton.isPressed()) return getText();
    if (RanButton.isPressed()) {
        formU.setText(std::to_string(mLib::GenerateRandomNum(maxSize)));
        formV.setText(std::to_string(mLib::GenerateRandomNum(maxSize)));
        formW.setText(std::to_string(mLib::GenerateRandomNum(maxSizeW)));
    }
    return {"", "", ""};
}