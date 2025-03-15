#include "appMenu.h"

Button AppMenu::addByValueButton(0, 800, 100, 25);
Button AppMenu::addAtIndexButton(0, 825, 100, 25);
Button AppMenu::addButton(0, 850, 100, 25);

ColorSet AppMenu::codeBlockColor{
    Color{173, 181, 189, 255}, Color{46, 52, 64, 255},
    Color{216, 222, 233, 255}, Color{211, 255, 206, 255},
    Color{59, 66, 82, 255}, Color{59, 66, 82, 255},
};

Button AppMenu::removeByValueButton({0, 875, 100, 25}, "Amogus", 20, DEF_SET);
Button AppMenu::removeAtIndexButton(100, 800, 100, 25);
Button AppMenu::removeButton(100, 825, 100, 25);

Vector2 AppMenu::codeBlockPosition{1250, 600};
Vector2 AppMenu::codeLineSize{300, 25};

Form AppMenu::locationBox{{200, 800, 500, 50}};
Form AppMenu::valueBox{{200, 900, 500, 50}};
std::vector<TextBox> AppMenu::codeList;
std::vector<GUIObject*> AppMenu::renderList;

void AppMenu::init() {
    codeList.resize(10);
    for (int i = 0; i < codeList.size(); i++) {
        float x = codeBlockPosition.x;
        float y = codeBlockPosition.y + i * codeLineSize.y;
        TextBox temp(Rectangle{x, y, codeLineSize.x, codeLineSize.y},
                     codeBlockColor, &DrawUtility::jbm20, "amogus");
        codeList[i] = temp;
        if (i % 2 == 0) codeList[i].setHighlight(true);
    }

    addByValueButton = Button(0, 800, 100, 25);
    addAtIndexButton = Button(0, 825, 100, 25);
    addButton = Button(0, 850, 100, 25);

    ColorSet codeBlockColor = {
        Color{173, 181, 189, 255}, Color{46, 52, 64, 255},
        Color{216, 222, 233, 255}, Color{211, 255, 206, 255},
        Color{216, 222, 233, 255}, Color{255, 114, 86, 255},
    };

    removeByValueButton = Button({0, 875, 100, 25}, "Amogus", 20,
                                        DEF_SET);
    removeAtIndexButton = Button (100, 800, 100, 25);
    removeButton = Button(100, 825, 100, 25);

    codeBlockPosition = {1250, 600};
    codeLineSize = {300, 25};

    locationBox = Form{{200, 800, 500, 50}};
    valueBox = Form{{200, 850, 500, 50}};
    renderList.push_back(&addByValueButton);
    renderList.push_back(&addAtIndexButton);
    renderList.push_back(&addButton);
    renderList.push_back(&removeByValueButton);
    renderList.push_back(&removeAtIndexButton);
    renderList.push_back(&removeButton);
    renderList.push_back(&locationBox);
    renderList.push_back(&valueBox);
}

void AppMenu::render() {
    for (GUIObject* object : renderList) {
        object->render();
        // std::cerr << "Rendering: " << object << "\n";
    }
    removeByValueButton.render();
    std::cerr << "Done\n";
    for (TextBox box : codeList) box.render();
}

void AppMenu::loadCode(const std::vector<std::string>& strVect) {
    for (int i = 0; i < codeList.size() && i < strVect.size(); i++)
        codeList[i].setText(strVect[i]);
}