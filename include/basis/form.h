#pragma once
#include <string>
#include <vector>
#include <utility>
#include "GUIObject.h"
#include "colorPalette.h"
#include "raylib.h"
#include "utility.h"
class Form : public GUIObject {
    bool enabled;
    std::string text;
    bool isFocusedOn;
    float width;
    float height;
    int LEFT_MARGIN;
    int RIGHT_MARGIN;
    int ABOVE_MARGIN;
    int BOTTOM_MARGIN;
    ColorSet PALETTE;
    constexpr static float BORDER_OFFSET = 1;
    void recordKeyboard();
    void recordFocus();

   public:
    Form(Rectangle drawInfo,
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
          text{""},
          enabled{true} {};

    void render();
    void update();
    void deFocus();
    std::string getText();
    std::pair<bool, int> getValue();

    void enable();
    void disable();
    void toggle();
};