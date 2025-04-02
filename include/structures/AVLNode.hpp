#ifndef AVLNODE_HPP
#define AVLNODE_HPP

#include "raylib.h"
#include "animation.h"
#include <map>

class AVLNode : public Animation {
    public:
        AVLNode *parent;
        AVLNode *left, *right;
        bool valid, targeted;
        int height, value, heightLeft, heightRight, balanceLeft, balanceRight, balance, targetValue, PosInParent;
        inline AVLNode(float x, float y, int value, AVLNode *parent, int P) : Animation(x, y), parent(parent), value(value), PosInParent(P) {
            left = right = NULL;
            valid = targeted = false;
            height = 1; balance = 0;
            heightLeft = heightRight = 0;
            balanceLeft = balanceRight = 0;
            targetValue = -1;
            setPosition((Vector2){x, y});
        }
        inline ~AVLNode() {
            if (left != NULL) delete left, left = NULL;
            if (right != NULL) delete right, right = NULL;
        }
};

#endif // AVLNODE_HPP