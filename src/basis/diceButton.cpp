#include "diceButton.hpp"

void DiceButton::setDimension(Vector2 dimension) {
    button.setDimension(dimension);
}

void DiceButton::setPosition(Vector2 position) {
    button.setPosition(position);
}

void DiceButton::render() {
    if (button.isHovered()) {
        Timer += GetFrameTime();
        std::cout << Timer << ' '<< loop << '\n';
        if (Timer > 0.2f) loop = (loop + 1) % 6, Timer = 0;
    }
    if (button.isPressed()) {
        loop = rand() % 6;
    }
    std::cout << loop << std::endl;
    //DrawTexture(mLib::diceTexture[loop], position.x, position.y, WHITE);
    DrawTexturePro(mLib::diceTexture[loop], {position.x, position.y, position.x + 128, position.y + 128}, 
    {position.x, position.y, position.x + 40, position.y + 40}, {0, 0}, 0, WHITE);
}

bool DiceButton::isPressed() const { return button.isPressed(); }

