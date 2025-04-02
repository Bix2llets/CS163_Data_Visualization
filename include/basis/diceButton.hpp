#ifndef DICEBUTTON_HPP
#define DICEBUTTON_HPP

#include "Button.h"
#include <mLib/Utility.hpp>
#include <cassert>

class DiceButton : public Button{
    private:
        float Timer;
        int loop;
    public:
    DiceButton(Vector2 position = {0, 0}, Vector2 dimension = {0, 0}, ColorSet const *palette = &buttonColorSet)
     : Button{position, dimension, "", 0,
              palette}, Timer{0}, loop{0} {
              };
    void render();
};

#endif // DICEBUTTON_HPP