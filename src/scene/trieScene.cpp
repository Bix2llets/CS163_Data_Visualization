#include "trieScene.h"

namespace TrieScene {
    TrieState Trie;

    void update() {
        Trie.update();
    }

    void handleInput() {
        Trie.handleInput();
    }
    
    void render() {
        Trie.render();
    }
}
