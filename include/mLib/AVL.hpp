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
        void calcPosition(AVLNode *root) ;
        void drawLine(AVLNode*root, int x, int y) ;
        void drawText(AVLNode *root, int x, int y) ;
        void draw(AVLNode *root, int x, int y) ;
        void drawItr(int x, int y) ;
        AVLNode *insertAnimation(AVLNode *root, int key) ;
        AVLNode *searchAnimation(AVLNode *root, int key) ;
        AVLNode *deleteAnimation(AVLNode *root, int key) ;
        void deleteNode(AVLNode* root, AVLNode *target) ;
        AVLNode *leftRotate(AVLNode *node);
        AVLNode *rightRotate(AVLNode *node);
        AVLNode *leftRightRotate(AVLNode *node);
        AVLNode *rightLeftRotate(AVLNode *node);
        std::vector<std::pair<AVLNode *, int> > InOrder(AVLNode *root, int level) ;
        Vector2 getPos(AVLNode *target, int x, int y) ;
        bool move(AVLNode *root) ;
        bool moveItr() ;
        std::vector<std::pair<int,  vWT> > working;
        std::vector<std::pair<Vector2, Vector2> > Itr;
        int itr1, itr2;
};


#endif // AVL_HPP