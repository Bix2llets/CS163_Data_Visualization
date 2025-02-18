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
    CREATE,
    DELETE,
    CLEAR,
    SETEND,
    SET_ITR_INSTANCE,
    SET_ITR_ANIMATION,
    DELETE_ITR,
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
        void drawItr(int x, int y) ;
        void insertAnimation(std::string word) ;
        void searchAnimation(std::string word) ;
        void deleteAnimation(std::string word) ;
        void deleteNode(TrieNode* root, TrieNode *target) ;
        Vector2 getPos(TrieNode *root, TrieNode *target, int x, int y) ;
        bool move(TrieNode *root) ;
        bool moveItr() ;
        std::vector<std::pair<int,  vWT> > working;
        std::vector<std::pair<Vector2, Vector2> > Itr;
        int itr1, itr2;
};


#endif // TRIE_HPP