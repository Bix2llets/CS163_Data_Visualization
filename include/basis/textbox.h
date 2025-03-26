#pragma once
#include <algorithm>
#include <iostream>
#include <string>

#include "GUIObject.h"
#include "colorPalette.h"
#include "raylib.h"
#include "utility.h"
#include "toggleable.h"
// * This provides no line wrapping, only box enlargement
class TextBox : public GUIObject, public Toggleable {
   private:
    bool isHighlighted = false;
    float width;
    float height;
    std::string text;
    Font* font;
    ColorSet color;
    constexpr static float OFFSET = 5;
    constexpr static float BORDER_OFFSET = 1;

    VerticalAlignment verticalAlign;
    HorizontalAlignment horizontalAlign;

   public:
    TextBox(Rectangle minimumBox = {0, 0, 0, 0}, ColorSet color = COLOR_SET_1,
            Font* renderFont = nullptr, std::string text = "",
            HorizontalAlignment horizontalAlign = HorizontalAlignment::CENTERED,
            VerticalAlignment verticalAlign = VerticalAlignment::CENTERED)
        : color{color},
          font{renderFont},
          text{text},
          GUIObject(minimumBox.x, minimumBox.y),
          width{minimumBox.width},
          height{minimumBox.height},
          verticalAlign{verticalAlign},
          horizontalAlign{horizontalAlign}, 
          Toggleable() {};

    void render();

    void setText(std::string newText);
    void setFont(Font* newFont);

    void setHighlight(bool newState);
};