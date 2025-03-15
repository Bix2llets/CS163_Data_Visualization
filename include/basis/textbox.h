// 
#include "GUIObject.h"
#include "raylib.h"
#include "utility.h"
#include "colorPalette.h"
#include <string>
#include <algorithm>
#include <iostream>
// * This provides no line wrapping, only box enlargement
class TextBox : public GUIObject {
    private:
    bool isHighlighted = false;
    float width;
    float height;
    std::string text;
    Font* font;
    ColorSet color;
    constexpr static float OFFSET = 5;
    constexpr static float BORDER_OFFSET = 1;
    public:

    TextBox(Rectangle minimumBox = {0, 0, 0, 0}, ColorSet color = DEF_SET, Font* renderFont = nullptr, std::string text = "") : color{color}, font{renderFont}, text{text}, GUIObject(minimumBox.x, minimumBox.y), width{minimumBox.width}, height{minimumBox.height} {};

    void render();

    void setText(std::string newText);
    void setFont(Font* newFont);

    void setHighlight(bool newState);
};