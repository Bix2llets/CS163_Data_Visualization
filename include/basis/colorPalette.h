#pragma once
#include "raylib.h"

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
struct ColorSet {
    Color textNormal;
    Color textHighlight;
    Color backgroundNormal;
    Color backgroundHighlight;
    bool renderBorder;
    Color border;
};
extern const ColorSet DEF_SET;
}  // namespace ColorPalette