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
const ColorSet DEF_SET = {FlatUI::CONCRETE, FlatUI::ASBESTOS, FlatUI::CLOUDS, FlatUI::SILVER, true, FlatUI::MIDNIGHT_BLUE};
}  // namespace ColorPalette