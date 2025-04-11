#pragma once
#include <vector>

#include "assert.h"
#include "button.h"
#include "diceButton.hpp"
#include "mForm.h"
#include "toggleable.h"
class MenuPane : public Toggleable, public GUIObject {
    std::vector<Button> btnList;
    std::vector<std::vector<mForm>> formList;
    std::vector<std::vector<std::string>> formTitleList;
    std::vector<bool> haveRandom;
    std::vector<DiceButton> diceButton;

    Color const* background;
    ColorSet const* buttonPalette;
    ColorSet const* formPalette;
    Vector2 dimension;

   public:
    static const Vector2 FORM_DIMENSION;
    static const Vector2 BUTTON_DIMENSION;
    static const Vector2 ELEMENT_DISTANCE;
    static const Vector2 EDGE_OFFSET;
    static const Vector2 RANDOM_DIMENSION;

    MenuPane(Vector2 STARTING_POSITION, Color const* background,
             ColorSet const* buttonPalette, ColorSet const* formPalette)
        : GUIObject(STARTING_POSITION),
          background{background},
          buttonPalette{buttonPalette},
          formPalette{formPalette} {}
    MenuPane()
        : GUIObject(Vector2{0, 0}),
          background{nullptr},
          buttonPalette{nullptr},
          formPalette{nullptr} {}
    void set(bool newState);
    void disable();
    void enable();
    void toggle();
    // 0 - based numbering
    std::string getText(int row, int col);
    bool isButtonPressed(int row);
    bool isRandomPressed(int row);
    Form& getForm(int row, int col);
    Button& getButton(int row);

    void newLine(int row, int numberOfForms, const std::string& buttonLabel,
                 const std::vector<std::string>& titleList,
                 const std::vector<bool>& formMode, bool haveRandom = false);
    void render();
    Vector2 getDimension();

    void calibrate();
};