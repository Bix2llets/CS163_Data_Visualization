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
        int mode;
        char character;
        float alpha;
        inline TrieNode(float x, float y, char character, TrieNode *parent) : Animation(x, y), parent(parent), character(character) {
            children.clear();
            isEndOfWord = valid = false;
            alpha = 0;
            mode = 0;
            setPosition((Vector2){x, y});
        }
        inline ~TrieNode() {
            for (auto &child : children) delete child.second;
            children.clear();
        }
        void setTarget() {
            mode = 1;
            alpha = 255.f;
        }
        void setUnTarget() {
            mode = 2;
            alpha = 0.f;
        }
        void updateAlpha(float currTime, float rate) {
            if (isCompletedAlpha()) return;
            if (mode == 0) return;
            if (mode == 1) {
                if (currTime >= rate) alpha = 0.f;
                else alpha = 255.f * (1 - currTime / rate);
                return ;
            }
            if (currTime >= rate) alpha = 255.f;
            else alpha = 255.f * (currTime / rate);
        }
        bool isCompletedAlpha() const {
            if (mode == 0) return true;
            if (mode == 1) return alpha <= 0.f;
            if (mode == 2) return alpha >= 255.f;
            return false;
        }
};

#endif // TRIENODE_HPP