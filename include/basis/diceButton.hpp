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
    public:
    DiceButton(Vector2 position, std::string text = "",
        int fontSize = 20, ColorSet palette = DEF_SET)
     : button{position, Vector2{0, 0}, text, fontSize,
              palette}, Timer{0}, loop{0}, position{position} {
                  button.setDimension((Vector2){40, 40});
              };
    void setDimension(Vector2 dimension);
    void setPosition(Vector2 position);
    void render();
    bool isPressed() const;
};

#endif // DICEBUTTON_HPP