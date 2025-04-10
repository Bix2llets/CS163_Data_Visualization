#include "appMenu.h"

namespace AppMenu {

ColorSet const* buttonPalette = &buttonColorSet;

ColorSet const* codeBlockColor = &buttonColorSet;

Vector2 panelPosition{50, 760};
Vector2 buttonDimension = {200, 40};
Vector2 codeBlockPosition{1050, 650};
Vector2 codeLineSize{500, 25};
Vector2 buttonDistance = {8, 8};
Button backButton({10, 10, buttonDimension.x, buttonDimension.y}, "Back",
                  DrawUtility::NORMAL_SIZE, buttonPalette);
Button colorModeButton({1600 - buttonDimension.x - 10, 10, buttonDimension.x, buttonDimension.y}, "", DrawUtility::NORMAL_SIZE, buttonPalette, &DrawUtility::inter20);

bool isDarkMode = false;
std::vector<TextBox> codeList;
std::vector<GUIObject*> renderList;

TextBox locationText({450, 760, buttonDimension.x / 2, buttonDimension.y},
                     buttonPalette, &DrawUtility::inter20, "Location: ");
TextBox valueText({450, 840, buttonDimension.x / 2, buttonDimension.y},
                  buttonPalette, &DrawUtility::inter20, "Value: ");

int* highlightValue = nullptr;
int verticalCellCount = 3;
int horizontalCellCount = 2;

void init() {
    codeList.resize(10);
    for (int i = 0; i < codeList.size(); i++) {
        float x = codeBlockPosition.x;
        float y = codeBlockPosition.y + i * codeLineSize.y;
        TextBox temp(Rectangle{x, y, codeLineSize.x, codeLineSize.y},
                     codeBlockColor, &DrawUtility::jbm20, "amogus",
                     HorizontalAlignment::LEFT);
        codeList[i] = temp;
        // ;if (i % 2 == 0) codeList[i].setHighlight(true);
    }
    isDarkMode = false;
    renderList.push_back(&backButton);
    // renderList.push_back(&colorModeButton);
}

void render() {
    if (highlightValue != nullptr) {
        if (*highlightValue == -1) {
            for (auto &x: codeList) x.disable();
        }
        else {
            for (auto &x: codeList) x.enable();
        }
        for (int i = 0; i < codeList.size(); i++)
            codeList[i].setHighlight(false);
        if (*highlightValue >= 0) codeList[*highlightValue].setHighlight(true);
    }
    else for (auto &x: codeList) x.disable();

    for (GUIObject* object : renderList) {
        object->render();
    }
    for (TextBox box : codeList) box.render();
    if (highlightValue != nullptr && *highlightValue >= 0)
        codeList[*highlightValue].render();
}

void loadCode(const std::vector<std::string>& strVect) {
    for (int i = 0; i < codeList.size(); i++)
        if (i < strVect.size())
            codeList[i].setText(strVect[i]);
        else
            codeList[i].setText("");
}

void setHighlight(int* index) { highlightValue = index; }

}  // namespace AppMenu