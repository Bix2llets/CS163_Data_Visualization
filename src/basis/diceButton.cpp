#include "diceButton.hpp"

void DiceButton::setDimension(Vector2 dimension) {
    button.setDimension(dimension);
}

void DiceButton::setPosition(Vector2 position) {
    button.setPosition(position);
}

void DiceButton::render() {
    button.render();
    if (button.isHovered()) {
        Timer += GetFrameTime();
        std::cout << Timer << ' '<< loop << '\n';
        if (Timer > 0.2f) loop = (loop + 1) % 16, Timer = 0;
    }
    if (button.isPressed()) {
        loop = rand() % 16;
    }
    std::cout << loop << std::endl;
    DrawTexturePro(mLib::dice, {loop * 260.f, 0, 260.f, 260.f}, 
    {position.x, position.y, dimension.x, dimension.y}, {0, 0}, 0, WHITE);
}

bool DiceButton::isPressed() const { return button.isPressed(); }

