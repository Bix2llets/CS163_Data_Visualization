#include "AVLScene.h"

namespace AVLScene {
    AVLState AVL;

    void update() {
        AVL.update();
    }

    void handleInput() {
        AVL.handleInput();
    }
    void render() {
        AVL.render();
    }
}