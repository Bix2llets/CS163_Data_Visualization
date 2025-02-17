#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include "raylib.h"
#include <unordered_map>

struct TrieNode {
    Vector2 position, targetPosition;
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    bool selected;
    bool highlighted;
    bool valid;
    TrieNode() {
        position = {0, 0};
        targetPosition = {0, 0};
        selected = false;
        highlighted = false;
        isEndOfWord = false;
        valid = false;
    }
};

#endif // TRIENODE_HPP