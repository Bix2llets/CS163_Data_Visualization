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
        float alpha;
        int mode;
        inline AVLNode(float x, float y, int value, AVLNode *parent, int P) : Animation(x, y), parent(parent), value(value), PosInParent(P) {
            left = right = NULL;
            valid = targeted = false;
            height = 1; balance = 0;
            heightLeft = heightRight = 0;
            balanceLeft = balanceRight = 0;
            targetValue = -1;
            setPosition((Vector2){x, y});
            mode = 0;
            alpha = 0;
        }
        inline ~AVLNode() {
            if (left != NULL) delete left, left = NULL;
            if (right != NULL) delete right, right = NULL;
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

#endif // AVLNODE_HPP