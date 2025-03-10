#pragma once
#include <string>
#include <vector>
#include <utility>
#include "GUIObject.h"
#include "colorPalette.h"
#include "raylib.h"
#include "utility.h"
class TextBox : public GUIObject {
    std::string text;
    bool isFocusedOn;
    float width;
    float height;
    const int LEFT_MARGIN;
    const int RIGHT_MARGIN;
    const int ABOVE_MARGIN;
    const int BOTTOM_MARGIN;
    const ColorSet PALETTE;

    void recordKeyboard();
    void recordFocus();

   public:
    TextBox(Rectangle drawInfo,
            ColorSet palette = DEF_SET)
        : GUIObject{drawInfo.x, drawInfo.y},
          width{drawInfo.width},
          height{drawInfo.height},
          PALETTE{palette},
          LEFT_MARGIN{10},
          RIGHT_MARGIN{10},
          ABOVE_MARGIN{10},
          BOTTOM_MARGIN{10},
          isFocusedOn{false},
          text{""} {};

    void render();
    void update();
    void deFocus();
    std::string getText();
    std::pair<bool, int> getValue();
};