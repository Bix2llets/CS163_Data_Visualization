#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include "raylib.h"
#include "TrieNode.hpp"

enum workingType
{
    SELECTING,
    HIGH_LIGHTING,
    CREATE,
    DELETE,
};

class Trie {
    private:
        float xOFFSET = 100, yOFFSET = 70, NODE_RADIUS = 20;
        Vector2 Lerp(Vector2 start, Vector2 end, float t) ;
        typedef std::vector<std::pair <workingType, TrieNode*> > vWT;
    public: 
        TrieNode* root;
        Trie() ;
        Vector2 calcPosition(TrieNode *root) ;
        void drawLine(TrieNode*root, int x, int y) ;
        void drawText(TrieNode *root, int x, int y) ;
        void draw(TrieNode *root, int x, int y) ;
        void insertAnimation(std::string word) ;
        bool move(TrieNode *root) ;
        std::vector<std::pair<int,  vWT> > working;
        int itr1, itr2;
};


#endif // TRIE_HPP