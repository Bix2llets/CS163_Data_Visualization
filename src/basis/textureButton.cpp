#include "textureButton.hpp"


void TextureBox::render() {
    if (!enabled) return;
    Button::render();
    DrawTexturePro(*texture, ori, {position.x, position.y, dimension.x, dimension.y}, {0, 0}, 0, getState() ? WHITE : Color{255, 255, 255, 100});
}


