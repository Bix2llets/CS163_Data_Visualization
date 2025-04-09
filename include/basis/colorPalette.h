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
extern const ColorSet COLOR_SET_LIGHT;
extern const ColorSet BUTTON_SET_LIGHT;
extern const ColorSet BACKGROUND_SET_LIGHT;
extern const ColorSet COLOR_SET_DARK;
extern const ColorSet BUTTON_SET_DARK;
extern const ColorSet BACKGROUND_SET_DARK;
extern ColorSet buttonColorSet;
extern ColorSet nodeColorSet;
extern ColorSet backgroundSet;
extern Color paneBackground;
extern Color nodeDragHighlight;
extern Color sliderIndicator;
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
}  // namespace GBDark

namespace GBLight {
extern Color BACKGROUND;
extern Color BACKGROUND0H;
extern Color BACKGROUND0;
extern Color BACKGROUND1;
extern Color BACKGROUND2;
extern Color BACKGROUND3;
extern Color BACKGROUND4;
extern Color BACKGROUND0S;
extern Color DARK_RED;
extern Color LIGHT_RED;
extern Color DARK_GREEN;
extern Color LIGHT_GREEN;
extern Color DARK_YELLOW;
extern Color LIGHT_YELLOW;
extern Color DARK_BLUE;
extern Color LIGHT_BLUE;
extern Color DARK_PURPLE;
extern Color LIGHT_PURPLE;
extern Color DARK_AQUA;
extern Color LIGHT_AQUA;
extern Color DARK_GRAY;
extern Color LIGHT_GRAY;
extern Color DARK_ORANGE;
extern Color LIGHT_ORANGE;
extern Color FOREGROUND;
extern Color FOREGROUND0;
extern Color FOREGROUND1;
extern Color FOREGROUND2;
extern Color FOREGROUND3;
extern Color FOREGROUND4;

}  // namespace GBLight

namespace TokyoNight {
extern ::Color NIGHT_RED;
extern ::Color NIGHT_ORANGE;
extern ::Color NIGHT_YELLOW;
extern ::Color NIGHT_WHITE;
extern ::Color NIGHT_GREEN;
extern ::Color NIGHT_CYAN;
extern ::Color NIGHT_TOOTHPASTE;
extern ::Color NIGHT_DIAMOND;
extern ::Color NIGHT_LIGHTBLUE;
extern ::Color NIGHT_DEEPBLUE;
extern ::Color NIGHT_PURPLE;
extern ::Color NIGHT_PALEPURPLE;
extern ::Color NIGHT_GRAY;
extern ::Color NIGHT_LIGHTGRAY;
extern ::Color NIGHT_DEEPGRAY;
extern ::Color NIGHT_MIDGRAY;
extern ::Color NIGHT_BLACK;
extern ::Color NIGHT_PURPLEBLACK;
extern ::Color NIGHT_LIGHTWHITE;

} // namespace TokyoNight