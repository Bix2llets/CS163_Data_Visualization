#include <mLib/mScene.hpp>

namespace mScene {
    AVLState avl;
    TrieState trie;
    HashState hash;
    void runAVL() {
        avl.run();
    }
    void runTrie() {
        trie.run();
    }
    void runHash() {
        hash.run();
    }
};