#pragma once
#include <string>
#include <utility>
#include <vector>

#include "GUIObject.h"
#include "colorPalette.h"
#include "raylib.h"
#include "toggleable.h"
#include "utility.h"

class Form : public GUIObject, public Toggleable {
   protected:
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
    virtual void recordKeyboard();
    void recordFocus();

   public:
    Form(Rectangle drawInfo, ColorSet const *palette = &buttonColorSet)
        : GUIObject{drawInfo.x, drawInfo.y},
          width{drawInfo.width},
          height{drawInfo.height},
          PALETTE{palette},
          LEFT_MARGIN{10},
          RIGHT_MARGIN{10},
          ABOVE_MARGIN{0},
          BOTTOM_MARGIN{0},
          isFocusedOn{false},
          text{""},
          Toggleable() {};

    virtual void render();
    virtual void update();
    void deFocus();
    void clear();
    void setText(std::string newText);
    void disable();
    void set(bool newState);
    std::string getText();
    std::pair<bool, int> getValue();

    inline Vector2 getDimension() { return Vector2{width, height}; };
    inline void setDimension(Vector2 newDim) {
        width = newDim.x;
        height = newDim.y;
    }
};