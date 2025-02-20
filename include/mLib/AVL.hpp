#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include "raylib.h"
#include "AVLNode.hpp"

enum workingType
{
    SELECTING,
    CREATE,
    DELETE,
    CLEAR,
    SET_ITR_INSTANCE,
    SET_ITR_ANIMATION,
    DELETE_ITR,
};

class AVL {
    private:
        float xOFFSET = 100, yOFFSET = 70, NODE_RADIUS = 20;
        Vector2 Lerp(Vector2 start, Vector2 end, float t) ;
        typedef std::vector<std::pair <workingType, AVLNode*> > vWT;
    public: 
        AVLNode* root;
        AVL() ;
        Vector2 calcPosition(AVLNode *root) ;
        void drawLine(AVLNode*root, int x, int y) ;
        void drawText(AVLNode *root, int x, int y) ;
        void draw(AVLNode *root, int x, int y) ;
        void drawItr(int x, int y) ;
        void insertAnimation(std::string word) ;
        void searchAnimation(std::string word) ;
        void deleteAnimation(std::string word) ;
        void deleteNode(AVLNode* root, AVLNode *target) ;
        void leftRotate(AVLNode *par, AVLNode *target) ;
        void rightRotate(AVLNode *par, AVLNode *target) ;
        void leftRightRotate(AVLNode *par, AVLNode *target) ;
        void rightLeftRotate(AVLNode *par, AVLNode *target) ;
        Vector2 getPos(AVLNode *root, AVLNode *target, int x, int y) ;
        bool move(AVLNode *root) ;
        bool moveItr() ;
        std::vector<std::pair<int,  vWT> > working;
        std::vector<std::pair<Vector2, Vector2> > Itr;
        int itr1, itr2;
};


#endif // AVL_HPP