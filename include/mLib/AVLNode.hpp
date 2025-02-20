#ifndef AVLNODE_HPP
#define AVLNODE_HPP

#include "raylib.h"
#include <map>

struct AVLNode {
    Vector2 position, targetPosition;
    AVLNode *left, *right;
    int data, balanceFactor;
    bool selected;
    bool valid;
    AVLNode() {
        position = {0, 0};
        targetPosition = {0, 0};
        selected = false;
        valid = false;
        left = right = nullptr;
        balanceFactor = 1;
        data = 0;
    }
};

#endif // AVLNODE_HPP