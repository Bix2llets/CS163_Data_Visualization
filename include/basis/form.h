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
    protected:
    std::string text;
    bool isFocusedOn;
    float width;
    float height;
    int LEFT_MARGIN;
    int RIGHT_MARGIN;
    private:
    int ABOVE_MARGIN;
    int BOTTOM_MARGIN;
    ColorSet PALETTE;
    constexpr static float BORDER_OFFSET = 1;
    virtual void recordKeyboard();
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
          Toggleable() {};

    void render();
    void update();
    void deFocus();
    std::string getText();
    std::pair<bool, int> getValue();
};