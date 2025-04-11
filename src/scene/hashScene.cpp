#include "hashScene.h"

namespace HashScene {
    HashState Hash;

    void update() {
        Hash.update();
    }

    void handleInput() {
        Hash.handleInput();
    }
    
    void render() {
        Hash.render();
    }
}
