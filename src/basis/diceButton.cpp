#include "diceButton.h"


void DiceButton::render() {
    Button::render();
    if (isHovered()) {
        Timer += GetFrameTime();
        if (Timer > 0.2f) loop = (loop + 1) % 16, Timer = 0;
    }
    if (isPressed()) {
        loop = rand() % 16;
    }
    DrawTexturePro(Utility::dice, {loop * 260.f, 0, 260.f, 260.f}, 
    {position.x, position.y, dimension.x, dimension.y}, {0, 0}, 0, WHITE);
}


