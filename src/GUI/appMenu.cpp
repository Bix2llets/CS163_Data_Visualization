#include "appMenu.h"

namespace AppMenu {

Button addByValueButton(0, 700, buttonDimension.x, buttonDimension.y, "add element",
                        DrawUtility::NORMAL_SIZE, buttonPalette);
Button addAtIndexButton(0, 740, buttonDimension.x, buttonDimension.y, "add at index",
                        DrawUtility::NORMAL_SIZE, buttonPalette);
Button addButton(0, 780, buttonDimension.x, buttonDimension.y, "Add",
                 DrawUtility::NORMAL_SIZE, buttonPalette);

Button removeByValueButton({200, 700, buttonDimension.x, buttonDimension.y},
                           "remove element", DrawUtility::NORMAL_SIZE,
                           buttonPalette);
Button removeAtIndexButton(200, 740, buttonDimension.x, buttonDimension.y,
                           "remove at index", DrawUtility::NORMAL_SIZE,
                           buttonPalette);
Button removeButton(200, 780, buttonDimension.x, buttonDimension.y, "Remove",
                    DrawUtility::NORMAL_SIZE, buttonPalette);

ColorSet buttonPalette = {
    Color{186, 180, 163, 255}, Color{186, 180, 163, 255},
    Color{51, 49, 45, 255},    Color{42, 114, 47, 255},
    Color{229, 189, 80, 255},  Color{229, 189, 80, 255},
};

ColorSet codeBlockColor{
    Color{173, 181, 189, 255}, Color{46, 52, 64, 255},
    Color{216, 222, 233, 255}, Color{211, 255, 206, 255},
    Color{59, 66, 82, 255},    Color{59, 66, 82, 255},
};

Vector2 buttonDimension = {200, 40};
Vector2 codeBlockPosition{1250, 600};
Vector2 codeLineSize{300, 25};

Form locationBox{{400, 700, 200, 40}, buttonPalette};
Form valueBox{{400, 740, 200, 40}, buttonPalette};
std::vector<TextBox> codeList;
std::vector<GUIObject*> renderList;

void init() {
    codeList.resize(10);
    for (int i = 0; i < codeList.size(); i++) {
        float x = codeBlockPosition.x;
        float y = codeBlockPosition.y + i * codeLineSize.y;
        TextBox temp(Rectangle{x, y, codeLineSize.x, codeLineSize.y},
                     codeBlockColor, &DrawUtility::jbm20, "amogus");
        codeList[i] = temp;
        if (i % 2 == 0) codeList[i].setHighlight(true);
    }
    renderList.push_back(&addByValueButton);
    renderList.push_back(&addAtIndexButton);
    renderList.push_back(&addButton);
    renderList.push_back(&removeByValueButton);
    renderList.push_back(&removeAtIndexButton);
    renderList.push_back(&removeButton);
    renderList.push_back(&locationBox);
    renderList.push_back(&valueBox);
}

void render() {
    for (GUIObject* object : renderList) {
        object->render();
        // std::cerr << "Rendering: " << object << "\n";
    }
    removeByValueButton.render();
    std::cerr << "Done\n";
    for (TextBox box : codeList) box.render();
}

void loadCode(const std::vector<std::string>& strVect) {
    for (int i = 0; i < codeList.size() && i < strVect.size(); i++)
        codeList[i].setText(strVect[i]);
}

}  // namespace AppMenu