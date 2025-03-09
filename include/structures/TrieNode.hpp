#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include "raylib.h"
#include <map>

struct TrieNode {
    Vector2 position, targetPosition;
    std::map<char, TrieNode*> children;
    bool isEndOfWord;
    bool selected;
    bool valid;
    TrieNode() {
        position = {0, 0};
        targetPosition = {0, 0};
        selected = false;
        isEndOfWord = false;
        valid = false;
    }
};

#endif // TRIENODE_HPP