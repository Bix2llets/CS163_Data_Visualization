#pragma once
#include <vector>

#include "button.h"
#include "form.h"
#include "toggleable.h"
#include "assert.h"
class MenuPane : public Toggleable {
    std::vector<Button> btnList;
    std::vector<std::vector<Form>> formList;
    std::vector<std::vector<std::string>> formTitleList;

    static const Vector2 FORM_DIMENSION;
    static const Vector2 BUTTON_DIMENSION;
    static const Vector2 ELEMENT_DISTANCE;
    static const Vector2 EDGE_OFFSET;
    const Vector2 STARTING_POSITION;
    Color const* background;
    ColorSet const* buttonPalette;
    ColorSet const* formPalette;
    
    public:
    MenuPane(Vector2 STARTING_POSITION, Color const* background,
             ColorSet const* buttonPalette, ColorSet const* formPalette)
        : STARTING_POSITION{STARTING_POSITION},
          background{background},
          buttonPalette{buttonPalette},
          formPalette{formPalette} {}
    void set(bool newState);
    void disable();
    void enable();
    void toggle();
    // 0 - based numbering
    std::string getText(int row, int col);
    bool getPressed(int row);

    Form& getForm(int row, int col);
    Button& getButton(int row);

    void newLine(int row, int numberOfForms, const std::string &buttonLabel, const std::vector<std::string> &titleList);
    void render();

};