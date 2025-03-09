#ifndef AVLNODE_HPP
#define AVLNODE_HPP

#include "raylib.h"
#include <map>

struct AVLNode {
    Vector2 position, targetPosition;
    AVLNode *left, *right;
    int data, height;
    bool selected;
    bool valid;
    AVLNode(int _data) {
        position = {0, 0};
        targetPosition = {0, 0};
        selected = false;
        valid = false;
        left = right = nullptr;
        height = 1;
        data = _data;
    }
    bool isLeaf() {
        return left == nullptr && right == nullptr;
    }
    int balanceFactor() {
        int leftHight = left == nullptr ? 0 : left->height;
        int rightHight = right == nullptr ? 0 : right->height;
        return leftHight - rightHight;
    }
};

#endif // AVLNODE_HPP