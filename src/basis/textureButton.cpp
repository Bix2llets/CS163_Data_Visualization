#include "textureButton.hpp"

void TextureBox::setDimension(Vector2 dimension) {
    button.setDimension(dimension);
}

void TextureBox::setPosition(Vector2 position) {
    button.setPosition(position);
}

void TextureBox::render() {
    button.render();
    DrawTexturePro(*texture, ori, {position.x, position.y, dimension.x, dimension.y}, {0, 0}, 0, getState() ? WHITE : Color{255, 255, 255, 100});
}

bool TextureBox::isPressed() const { return button.isPressed(); }

