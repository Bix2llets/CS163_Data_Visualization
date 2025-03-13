#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include "raylib.h"
#include "animation.h"
#include <map>

class TrieNode : public Animation {
    public:
        TrieNode *parent;
        std::map<char, TrieNode*> children;
        bool isEndOfWord, valid;
        char character;
        inline TrieNode(int x, int y, char character, TrieNode *parent) : Animation(x, y), parent(parent), character(character) {
            parent = NULL;
            children.clear();
            isEndOfWord = valid = false;
            character = '\0';
            setPosition((Vector2){x, y});
        }
        inline ~TrieNode() {
            for (auto &child : children) delete child.second;
            children.clear();
        }
};

#endif // TRIENODE_HPP