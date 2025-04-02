#ifndef MSCENE_HPP
#define MSCENE_HPP

#include "AVLState.hpp"
#include "TrieState.hpp"
#include "hashState.hpp"

namespace mScene {
    extern AVLState avl;
    extern TrieState trie;
    extern HashState hash;
    void runAVL();
    void runTrie();
    void runHash();
};

#endif // MSCENE_HPP