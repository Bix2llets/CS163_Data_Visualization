#include "appMenu.h"

namespace AppMenu {

ColorSet const* buttonPalette = &BUTTON_SET_1;

ColorSet const* codeBlockColor = new ColorSet{
    Color{46, 52, 64, 255},    Color{46, 52, 64, 255},
    Color{216, 222, 233, 255}, Color{211, 255, 206, 255},
    Color{59, 66, 82, 255},    Color{59, 66, 82, 255},
};

Vector2 panelPosition{50, 760};
Vector2 buttonDimension = {200, 40};
Vector2 codeBlockPosition{1050, 520};
Vector2 codeLineSize{500, 25};
Vector2 buttonDistance = {8, 8};
std::vector<std::vector<Button>> buttonPanel;
Button backButton({10, 10, buttonDimension.x, buttonDimension.y}, "Back",
                  DrawUtility::NORMAL_SIZE, buttonPalette);

Button undoButton({800, 0}, buttonDimension, "undo", DrawUtility::NORMAL_SIZE,
                  buttonPalette);
Button redoButton({800, buttonDimension.y}, buttonDimension, "redo",
                  DrawUtility::NORMAL_SIZE, buttonPalette);
Button backwardButton({1000, 0}, buttonDimension, "undo", DrawUtility::NORMAL_SIZE,
                  buttonPalette);
Button forwardButton({1000, buttonDimension.y}, buttonDimension, "redo",
                  DrawUtility::NORMAL_SIZE, buttonPalette);
Button togglePauseButton({800, buttonDimension.y * 2}, buttonDimension,
                         "toggle Pause", DrawUtility::NORMAL_SIZE,
                         buttonPalette);

Form locationBox{{550, 760, 200, 40}, buttonPalette};
Form valueBox{{550, 840, 200, 40}, buttonPalette};

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
    codeList.resize(15);
    for (int i = 0; i < codeList.size(); i++) {
        float x = codeBlockPosition.x;
        float y = codeBlockPosition.y + i * codeLineSize.y;
        TextBox temp(Rectangle{x, y, codeLineSize.x, codeLineSize.y},
                     codeBlockColor, &DrawUtility::jbm20, "amogus",
                     HorizontalAlignment::LEFT);
        codeList[i] = temp;
        // ;if (i % 2 == 0) codeList[i].setHighlight(true);
    }

    buttonPanel.resize(verticalCellCount);
    for (std::vector<Button>& v : buttonPanel) v.resize(horizontalCellCount);

    for (int i = 0; i < buttonPanel.size(); i++)
        for (int j = 0; j < buttonPanel[i].size(); j++) {
            buttonPanel[i][j] = Button(
                {
                    panelPosition.x + buttonDimension.x * j +
                        buttonDistance.x * j,
                    panelPosition.y + buttonDimension.y * i +
                        buttonDistance.y * i,
                    buttonDimension.x,
                    buttonDimension.y,
                },
                "", DrawUtility::NORMAL_SIZE, &BUTTON_SET_1);
            buttonPanel[i][j].enable();
            renderList.push_back(&buttonPanel[i][j]);
        }
    renderList.push_back(&valueBox);
    renderList.push_back(&locationBox);
    renderList.push_back(&backButton);
    renderList.push_back(&valueText);
    renderList.push_back(&locationText);
    renderList.push_back(&undoButton);
    renderList.push_back(&redoButton);
    renderList.push_back(&backwardButton);
    renderList.push_back(&forwardButton);
    renderList.push_back(&togglePauseButton);
}

void render() {
    if (highlightValue != nullptr) {
        for (int i = 0; i < codeList.size(); i++)
            codeList[i].setHighlight(false);
        if (*highlightValue >= 0) codeList[*highlightValue].setHighlight(true);
    }

    for (GUIObject* object : renderList) {
        object->render();
    }
    for (TextBox box : codeList) box.render();
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