#include "AVL.hpp"

AVL::AVL() {
    root = new AVLNode();
    working.clear();
    itr1 = 0, itr2 = 0;
    Itr.clear();
}

Vector2 AVL::Lerp(Vector2 start, Vector2 end, float t) {
    Vector2 direction = {end.x - start.x, end.y - start.y};
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 1.0)
        {
            direction.x /= length;
            direction.y /= length;
            return {start.x + direction.x * t, start.y + direction.y * t};
        }
        return end;
}

Vector2 AVL::calcPosition(AVLNode *root) {
}

void AVL::drawLine(AVLNode*root, int x, int y) {
}

void AVL::drawText(AVLNode *root, int x, int y)
{
}

void AVL::draw(AVLNode *root, int x, int y) {
}

Vector2 AVL::getPos(AVLNode *root, AVLNode *target, int x, int y) {
}

void AVL::drawItr(int x, int y)
{
}

void AVL::insertAnimation(std::string word) {
}

void AVL::searchAnimation(std::string word) {
}

void AVL::deleteAnimation(std::string word) {
}

void AVL::deleteNode(AVLNode* root, AVLNode *target) {
}

bool AVL::move(AVLNode *root)
{
}

bool AVL::moveItr()
{
}

void AVL::leftRotate(AVLNode *par, AVLNode *target) {
    AVLNode *temp = target->right;
    target->right = temp->left;
    temp->left = target;
    if (par == NULL)
    {
        root = temp;
    }
    else if (par->left == target)
    {
        par->left = temp;
    }
    else
    {
        par->right = temp;
    }
}

void AVL::rightRotate(AVLNode *par, AVLNode *target) {
    AVLNode *temp = target->left;
    target->left = temp->right;
    temp->right = target;
    if (par == NULL)
    {
        root = temp;
    }
    else if (par->left == target)
    {
        par->left = temp;
    }
    else
    {
        par->right = temp;
    }
}

void AVL::rightLeftRotate(AVLNode *par, AVLNode *target) {
    rightRotate(target, target->right);
    leftRotate(par, target);
}

void AVL::leftRightRotate(AVLNode *par, AVLNode *target) {
    leftRotate(target, target->left);
    rightRotate(par, target);
}