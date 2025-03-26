#pragma once
#include "raylib.h"
struct ColorSet {
    Color textNormal;
    Color textHighlight;
    Color backgroundNormal;
    Color backgroundHighlight;
    Color borderNormal;
    Color borderHighlight;
};
extern const ColorSet DEF_SET;

namespace ColorPalette {
const int MAX_TRANSPARENCY = 255;
namespace FlatUI {
extern ::Color TURQUOISE;
extern ::Color EMERALD;
extern ::Color PETER_RIVER;
extern ::Color AMETHYST;
extern ::Color WET_ASPHALT;
extern ::Color GREEN_SEA;
extern ::Color NEPHRITIS;
extern ::Color BELIZE_HOLE;
extern ::Color WISTERIA;
extern ::Color MIDNIGHT_BLUE;
extern ::Color SUN_FLOWER;
extern ::Color CARROT;
extern ::Color ALIZARIN;
extern ::Color CLOUDS;
extern ::Color CONCRETE;
extern ::Color FLAT_ORANGE;
extern ::Color PUMPKIN;
extern ::Color POMEGRANATE;
extern ::Color SILVER;
extern ::Color ASBESTOS;
};  // namespace FlatUI
Color getTransparency(Color color, float tranperencyRatio);
}  // namespace ColorPalette

namespace GBDark {
    extern const Color BACKGROUND;
    extern const Color BACKGROUND0H;
    extern const Color BACKGROUND0;
    extern const Color BACKGROUND1;
    extern const Color BACKGROUND2;
    extern const Color BACKGROUND3;
    extern const Color BACKGROUND4;
    extern const Color BACKGROUND0S;
    extern const Color DARK_RED;
    extern const Color LIGHT_RED;
    extern const Color DARK_GREEN;
    extern const Color LIGHT_GREEN;
    extern const Color DARK_YELLOW;
    extern const Color LIGHT_YELLOW;
    extern const Color DARK_BLUE;
    extern const Color LIGHT_BLUE;
    extern const Color DARK_PURPLE;
    extern const Color LIGHT_PURPLE;
    extern const Color DARK_AQUA;
    extern const Color LIGHT_AQUA;
    extern const Color DARK_GRAY;
    extern const Color LIGHT_GRAY;
    extern const Color DARK_ORANGE;
    extern const Color LIGHT_ORANGE;
    extern const Color FOREGROUND;
    extern const Color FOREGROUND0;
    extern const Color FOREGROUND1;
    extern const Color FOREGROUND2;
    extern const Color FOREGROUND3;
    extern const Color FOREGROUND4;
}

namespace GBLight {
    extern const Color BACKGROUND;
    extern const Color BACKGROUND0H;
    extern const Color BACKGROUND0;
    extern const Color BACKGROUND1;
    extern const Color BACKGROUND2;
    extern const Color BACKGROUND3;
    extern const Color BACKGROUND4;
    extern const Color BACKGROUND0S;
    extern const Color DARK_RED;
    extern const Color LIGHT_RED;
    extern const Color DARK_GREEN;
    extern const Color LIGHT_GREEN;
    extern const Color DARK_YELLOW;
    extern const Color LIGHT_YELLOW;
    extern const Color DARK_BLUE;
    extern const Color LIGHT_BLUE;
    extern const Color DARK_PURPLE;
    extern const Color LIGHT_PURPLE;
    extern const Color DARK_AQUA;
    extern const Color LIGHT_AQUA;
    extern const Color DARK_GRAY;
    extern const Color LIGHT_GRAY;
    extern const Color DARK_ORANGE;
    extern const Color LIGHT_ORANGE;
    extern const Color FOREGROUND;
    extern const Color FOREGROUND0;
    extern const Color FOREGROUND1;
    extern const Color FOREGROUND2;
    extern const Color FOREGROUND3;
    extern const Color FOREGROUND4;
    
}