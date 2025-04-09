#include "colorPalette.h"

#include "math.h"
#include "raylib.h"
namespace ColorPalette {
namespace FlatUI {
::Color TURQUOISE{26, 188, 156, 255};
::Color EMERALD{46, 204, 113, 255};
::Color PETER_RIVER{52, 152, 219, 255};
::Color AMETHYST{155, 89, 182, 255};
::Color WET_ASPHALT{52, 73, 94, 255};
::Color GREEN_SEA{22, 160, 133, 255};
::Color NEPHRITIS{39, 174, 96, 255};
::Color BELIZE_HOLE{41, 128, 185, 255};
::Color WISTERIA{142, 68, 173, 255};
::Color MIDNIGHT_BLUE{44, 62, 80, 255};
::Color SUN_FLOWER{241, 196, 15, 255};
::Color CARROT{230, 126, 34, 255};
::Color ALIZARIN{231, 76, 60, 255};
::Color CLOUDS{236, 240, 241, 255};
::Color CONCRETE{149, 165, 166, 255};
::Color FLAT_ORANGE{243, 156, 18, 255};
::Color PUMPKIN{211, 84, 0, 255};
::Color POMEGRANATE{192, 57, 43, 255};
::Color SILVER{189, 195, 199, 255};
::Color ASBESTOS{127, 140, 141, 255};
}  // namespace FlatUI
Color getTransparency(Color color, float transparencyRatio) {
    if (transparencyRatio < 0) transparencyRatio = 0;
    if (transparencyRatio > 0) transparencyRatio = 1;
    float transparency = transparencyRatio * color.a * MAX_TRANSPARENCY;
    return Color{color.r, color.g, color.b,
                 (unsigned char)(round(transparency))};
}
}  // namespace ColorPalette

namespace GBDark {
const Color BACKGROUND = GetColor(0x282828ff);
const Color BACKGROUND0H = GetColor(0x1d2021ff);
const Color BACKGROUND0 = GetColor(0x282828ff);
const Color BACKGROUND1 = GetColor(0x3c3836ff);
const Color BACKGROUND2 = GetColor(0x504945ff);
const Color BACKGROUND3 = GetColor(0x665c54ff);
const Color BACKGROUND4 = GetColor(0x7c6f64ff);
const Color BACKGROUND0S = GetColor(0x928374ff);
const Color DARK_RED = GetColor(0xcc241dff);
const Color LIGHT_RED = GetColor(0xfb4934ff);
const Color DARK_GREEN = GetColor(0x98971aff);
const Color LIGHT_GREEN = GetColor(0xb8bb26ff);
const Color DARK_YELLOW = GetColor(0xd79921ff);
const Color LIGHT_YELLOW = GetColor(0xfabd2fff);
const Color DARK_BLUE = GetColor(0x458588ff);
const Color LIGHT_BLUE = GetColor(0x83a598ff);
const Color DARK_PURPLE = GetColor(0xb16286ff);
const Color LIGHT_PURPLE = GetColor(0xd3869bff);
const Color DARK_AQUA = GetColor(0x689d6aff);
const Color LIGHT_AQUA = GetColor(0x8ec07cff);
const Color DARK_GRAY = GetColor(0x928374ff);
const Color LIGHT_GRAY = GetColor(0xa89984ff);
const Color DARK_ORANGE = GetColor(0xd65d0eff);
const Color LIGHT_ORANGE = GetColor(0xfe8019ff);
const Color FOREGROUND = GetColor(0xebdbb2ff);
const Color FOREGROUND0 = GetColor(0xfbf1c7ff);
const Color FOREGROUND1 = GetColor(0xebdbb2ff);
const Color FOREGROUND2 = GetColor(0xd5c4a1ff);
const Color FOREGROUND3 = GetColor(0xbdae93ff);
const Color FOREGROUND4 = GetColor(0xa89984ff);
};  // namespace GBDark

namespace GBLight {
Color BACKGROUND = GetColor(0xFBF1C7ff);
Color BACKGROUND0H = GetColor(0xF9F5D7ff);
Color BACKGROUND0 = GetColor(0xFBF1C7ff);
Color BACKGROUND1 = GetColor(0xEBDBB2ff);
Color BACKGROUND2 = GetColor(0xD5C4A1ff);
Color BACKGROUND3 = GetColor(0xBDAE93ff);
Color BACKGROUND4 = GetColor(0xA89984ff);
Color BACKGROUND0S = GetColor(0xF2E5BCff);
Color DARK_RED = GetColor(0x9D0006ff);
Color LIGHT_RED = GetColor(0xCC241Dff);
Color DARK_GREEN = GetColor(0x79740Eff);
Color LIGHT_GREEN = GetColor(0x98971Aff);
Color DARK_YELLOW = GetColor(0xB57614ff);
Color LIGHT_YELLOW = GetColor(0xD79921ff);
Color DARK_BLUE = GetColor(0x076678ff);
Color LIGHT_BLUE = GetColor(0x458588ff);
Color DARK_PURPLE = GetColor(0x8F3F71ff);
Color LIGHT_PURPLE = GetColor(0xB16286ff);
Color DARK_AQUA = GetColor(0x427B58ff);
Color LIGHT_AQUA = GetColor(0x689D6Aff);
Color DARK_GRAY = GetColor(0x7C6F64ff);
Color LIGHT_GRAY = GetColor(0x928374ff);
Color DARK_ORANGE = GetColor(0xAF3A03ff);
Color LIGHT_ORANGE = GetColor(0xD65D0Eff);
Color FOREGROUND = GetColor(0x3C3836ff);
Color FOREGROUND0 = GetColor(0x282828ff);
Color FOREGROUND1 = GetColor(0x3C3836ff);
Color FOREGROUND2 = GetColor(0x504945ff);
Color FOREGROUND3 = GetColor(0x665C54ff);
Color FOREGROUND4 = GetColor(0x7C6F64ff);

}  // namespace GBLight

namespace TokyoNight {
::Color NIGHT_RED = GetColor(0xf7768eFF);
::Color NIGHT_ORANGE = GetColor(0xff9e64FF);
::Color NIGHT_YELLOW = GetColor(0xe0af68FF);
::Color NIGHT_WHITE = GetColor(0xcfc9c2FF);
::Color NIGHT_GREEN = GetColor(0x9ece6aFF);
::Color NIGHT_CYAN = GetColor(0x73dacaFF);
::Color NIGHT_TOOTHPASTE = GetColor(0xb4f9f8FF);
::Color NIGHT_DIAMOND = GetColor(0x2ac3deFF);
::Color NIGHT_LIGHTBLUE = GetColor(0x7dcfffFF);
::Color NIGHT_DEEPBLUE = GetColor(0x7aa2f7FF);
::Color NIGHT_PURPLE = GetColor(0xbb9af7FF);
::Color NIGHT_PALEPURPLE = GetColor(0xc0caf5FF);
::Color NIGHT_GRAY = GetColor(0xa9b1d6FF);
::Color NIGHT_LIGHTGRAY = GetColor(0x9aa5ceFF);
::Color NIGHT_DEEPGRAY = GetColor(0x565f89FF);
::Color NIGHT_MIDGRAY = GetColor(0x414868FF);
::Color NIGHT_BLACK = GetColor(0x24283bFF);
::Color NIGHT_PURPLEBLACK = GetColor(0x1a1b26FF);
}  // namespace TokyoNight
const ColorSet COLOR_SET_LIGHT = {
    GBLight::FOREGROUND2, GBLight::FOREGROUND0, GBLight::BACKGROUND2,
    GBLight::BACKGROUND3, GBLight::FOREGROUND0, GBLight::DARK_YELLOW,
};
const ColorSet BUTTON_SET_LIGHT = {GBLight::FOREGROUND2, GBLight::FOREGROUND0,
                                   GBLight::BACKGROUND2, GBLight::BACKGROUND4,
                                   GBLight::FOREGROUND0, GBLight::FOREGROUND0};

const ColorSet COLOR_SET_DARK = {
    TokyoNight::NIGHT_GRAY, TokyoNight::NIGHT_DIAMOND, 
    TokyoNight::NIGHT_MIDGRAY, TokyoNight::NIGHT_PURPLEBLACK,
    TokyoNight::NIGHT_LIGHTGRAY, TokyoNight::NIGHT_ORANGE
};

const ColorSet BUTTON_SET_DARK = {
    TokyoNight::NIGHT_LIGHTBLUE, TokyoNight::NIGHT_TOOTHPASTE, 
    TokyoNight::NIGHT_MIDGRAY, TokyoNight::NIGHT_BLACK,
    TokyoNight::NIGHT_PALEPURPLE, TokyoNight::NIGHT_PURPLE
};

const ColorSet BACKGROUND_SET_LIGHT = {
    GBLight::BACKGROUND3, GBLight::BACKGROUND3,
    GBDark::BACKGROUND0S, GBLight::BACKGROUND4,
    GBLight::FOREGROUND4, GBLight::FOREGROUND4
};
const ColorSet BACKGROUND_SET_DARK = {
    TokyoNight::NIGHT_CYAN, TokyoNight::NIGHT_DEEPBLUE,
    TokyoNight::NIGHT_MIDGRAY, TokyoNight::NIGHT_BLACK,
    TokyoNight::NIGHT_LIGHTGRAY, TokyoNight::NIGHT_LIGHTGRAY,
};

ColorSet buttonColorSet;
ColorSet nodeColorSet;
ColorSet backgroundSet;
Color paneBackground;
Color nodeDragHighlight;
Color sliderIndicator;