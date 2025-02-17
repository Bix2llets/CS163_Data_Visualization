#include <string>
#include <vector>

#include "GUIObject.h"
#include "colorPalette.h"
#include "raylib.h"
#include "utility.h"
class TextBox : public GUIObject {
    std::string text;
    bool isFocusedOn;
    float width;
    float height;
    const int LEFT_MARGIN;
    const int RIGHT_MARGIN;
    const int ABOVE_MARGIN;
    const int BOTTOM_MARGIN;
    const ColorPalette::ColorSet PALETTE;
    static std::vector<TextBox> boxList;

   public:
    TextBox(Rectangle drawInfo,
            ColorPalette::ColorSet palette =
                {ColorPalette::FlatUI::AMETHYST, ColorPalette::FlatUI::WISTERIA,
                 ColorPalette::FlatUI::CLOUDS, ColorPalette::FlatUI::SILVER,
                 true, ColorPalette::FlatUI::WET_ASPHALT},
            int fontSize)
        : GUIObject{drawInfo.x, drawInfo.y},
          width{drawInfo.width},
          height{drawInfo.height},
          PALETTE{palette},
          LEFT_MARGIN{10},
          RIGHT_MARGIN{10},
          ABOVE_MARGIN{10},
          BOTTOM_MARGIN{10} {};

    void render();
    static void recordKeyboard();
    static void recordFocus();
};