#pragma once
#include <string>
#include <vector>
#include <utility>
#include "GUIObject.h"
#include "colorPalette.h"
#include "raylib.h"
#include "utility.h"
#include "toggleable.h"
class Form : public GUIObject, public Toggleable {
    std::string text;
    bool isFocusedOn;
    float width;
    float height;
    int LEFT_MARGIN;
    int RIGHT_MARGIN;
    int ABOVE_MARGIN;
    int BOTTOM_MARGIN;
    ColorSet const *PALETTE;
    constexpr static float BORDER_OFFSET = 1;
    void recordKeyboard();
    void recordFocus();

   public:
    Form(Rectangle drawInfo,
            ColorSet const *palette = &BUTTON_SET_1)
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
          Toggleable() {};

    void render();
    void update();
    void deFocus();
    void clear();
    std::string getText();
    std::pair<bool, int> getValue();

};