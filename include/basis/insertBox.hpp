#ifndef INSERTBOX_HPP
#define INSERTBOX_HPP
#include "diceButton.hpp"
#include "textbox.h"
#include "mForm.h"

class InsertBox {
    private:
        TextBox textBox;
        mForm form;
        DiceButton RanButton;
        Button submitButton;
        bool mode; // 0 for num, 1 for text
        int maxSize;
        Vector2 position, dimension;
    public:
        InsertBox (Vector2 position, Vector2 dimension, int fontSize = 20, ColorSet const* palette = &BUTTON_SET_1, bool mode = 0, int maxSize = 100)
            : textBox{{position.x, position.y, dimension.x / 2, dimension.y}, palette, &DrawUtility::inter20, mode == 0 ? "Num: " : "Text: "},
              form{{position.x + dimension.x / 2, position.y, dimension.x, dimension.y}, palette, mode, maxSize},
              RanButton{(Vector2){position.x + dimension.x / 2 + dimension.x, position.y}, (Vector2){dimension.y, dimension.y}, palette}, 
              submitButton{(Vector2){position.x + dimension.x / 2 + dimension.x + dimension.y, position.y}, (Vector2){dimension.y, dimension.y}, "Enter", fontSize, palette}, 
              mode(mode), 
              maxSize(maxSize), 
                position(position),
                dimension(dimension) {
              };
        std::string render() {
            std::string inform = handleInput();
            form.render();
            textBox.render();
            RanButton.render();
            submitButton.render();
            std::cout << "request inform" << inform << std::endl;
            return inform;
        };
        std::string getText() {
            return form.getText();
        };
        std::string handleInput();
};

#endif // INSERTBOX_HPP