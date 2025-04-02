#ifndef EDGEINSERTBOX_HPP
#define EDGEINSERTBOX_HPP
#include "diceButton.hpp"
#include "mForm.h"
#include "textbox.h"

class edgeInsertBox {
   private:
    TextBox textBoxU, textBoxV, textBoxW;
    mForm formU, formV, formW;
    DiceButton RanButton;
    Button submitButton;
    bool mode;  // 0 for num, 1 for text
    int maxSize, maxSizeW;
    Vector2 position, dimension;

   public:
    edgeInsertBox(Vector2 position, Vector2 dimension, int fontSize = 20,
                  ColorSet const *palette = &BUTTON_SET_1, bool mode = 0,
                  int maxSize = 100, int maxSizeW = 100)
        : textBoxU{{position.x, position.y, dimension.x / 2, dimension.y},
                   palette,
                   &DrawUtility::inter20,
                   "U:"},
          formU{{position.x + dimension.x / 2, position.y, dimension.x,
                 dimension.y},
                palette,
                mode,
                maxSize},
          textBoxV{{position.x, position.y + dimension.y, dimension.x / 2,
                    dimension.y},
                   palette,
                   &DrawUtility::inter20,
                   "V:"},
          formV{{position.x + dimension.x / 2, position.y + dimension.y,
                 dimension.x, dimension.y},
                palette,
                mode,
                maxSize},
          textBoxW{{position.x, position.y + dimension.y * 2, dimension.x / 2,
                    dimension.y},
                   palette,
                   &DrawUtility::inter20,
                   "W:"},
          formW{{position.x + dimension.x / 2, position.y + dimension.y * 2,
                 dimension.x, dimension.y},
                palette,
                mode,
                maxSizeW},
          RanButton{
              (Vector2){position.x + dimension.x / 2 + dimension.x, position.y},
              (Vector2){dimension.y, dimension.y}, palette},
          submitButton{(Vector2){position.x + dimension.x / 2 + dimension.x +
                                     dimension.y,
                                 position.y},
                       (Vector2){dimension.y, dimension.y}, "Enter", fontSize,
                       palette},
          mode(mode),
          maxSize(maxSize),
          maxSizeW(maxSizeW),
          position(position),
          dimension(dimension) {};
    std::vector<std::string> render() {
        std::vector<std::string> inform = handleInput();
        formU.render();
        formV.render();
        formW.render();
        textBoxU.render();
        textBoxV.render();
        textBoxW.render();
        RanButton.render();
        submitButton.render();
        return inform;
    };
    std::vector<std::string> getText() {
        std::vector<std::string> inform;
        inform.push_back(formU.getText());
        inform.push_back(formV.getText());
        inform.push_back(formW.getText());
        return inform;
    };
    std::vector<std::string> handleInput();
};

#endif  // EDGEINSERTBOX_HPP