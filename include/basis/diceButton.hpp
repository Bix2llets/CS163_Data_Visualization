#ifndef DICEBUTTON_HPP
#define DICEBUTTON_HPP

#include "Button.h"
#include <mLib/Utility.hpp>
#include <cassert>

class DiceButton{
    private:
        Button button;
        float Timer;
        int loop;
        Vector2 position;
        Vector2 dimension;
    public:
    DiceButton(Vector2 position, Vector2 dimension, std::string text = "",
        int fontSize = 20, ColorSet const *palette = &BUTTON_SET_1)
     : button{position, dimension, text, fontSize,
              palette}, Timer{0}, loop{0}, position{position}, dimension{dimension} {
              };
    void setDimension(Vector2 dimension);
    void setPosition(Vector2 position);
    void render();
    bool isPressed() const;
};

#endif // DICEBUTTON_HPP