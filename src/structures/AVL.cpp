#include "AVL.hpp"

AVL::AVL() {
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

void AVL::calcPosition(AVLNode *root) {
    std::vector<std::pair<AVLNode *, int> > inOrder = InOrder(root, 0);
    int mid = inOrder.size() / 2;
    for (int i = 0; i < inOrder.size(); i++) 
        inOrder[i].first->targetPosition = {(i - mid) * xOFFSET, inOrder[i].second * yOFFSET};
}

std::vector<std::pair<AVLNode *, int> > AVL::InOrder(AVLNode *root, int level) {
    std::vector<std::pair<AVLNode *, int> > result;
    if (root == NULL) return result;
    std::vector<std::pair<AVLNode *, int> > left = InOrder(root->left, level + 1);
    result.insert(result.end(), left.begin(), left.end());
    result.push_back({root, level});
    std::vector<std::pair<AVLNode *, int> > right = InOrder(root->right, level + 1);
    result.insert(result.end(), right.begin(), right.end());
    return result;
}

void AVL::drawLine(AVLNode*root, int x, int y) {
    if (root == NULL) {
        return ;
    }
    if (root->left != NULL && root->left->valid) {
        DrawLine(x + root->position.x, y + root->position.y, x + root->left->position.x, y + root->left->position.y, RED);
        drawLine(root->left, x, y);   
    }
    if (root->right != NULL && root->right->valid) {
        DrawLine(x + root->position.x, y + root->position.y, x + root->right->position.x, y + root->right->position.y, RED);
        drawLine(root->right, x, y);
    }
}

void AVL::drawText(AVLNode *root, int x, int y)
{
    if (root == NULL) {
        return ;
    }
    if (root -> valid == 0) return ;
    DrawText(std::to_string(root->data).c_str(), x + root->position.x - 10, y + root->position.y - 10, 20, WHITE);
    if (root->left != NULL && root->left->valid) drawText(root->left, x, y);
    if (root->right != NULL && root->right->valid) drawText(root->right, x, y);
}

void AVL::draw(AVLNode *root, int x, int y) {
    if (root == NULL) {
        return;
    }
    if (root -> selected) DrawRing((Vector2){x, y}, NODE_RADIUS, NODE_RADIUS + 5, 0, 360, 20, RED);
    DrawCircle(x, y, NODE_RADIUS, PURPLE);
    if (root->left != NULL && root->left->valid) draw(root->left, root->left->position.x + x, root->left->position.y + y);
    if (root->right != NULL && root->right->valid) draw(root->right, root->right->position.x + x, root->right->position.y + y);
}

void AVL::drawItr(int x, int y)
{
    for (int i = 0; i < Itr.size(); i ++) 
        if (Itr[i].first.x != -1)
            DrawRing((Vector2){Itr[i].first.x + x, Itr[i].first.y + y}, NODE_RADIUS, NODE_RADIUS + 5, 0, 360, 20, GREEN);
}
Vector2 AVL::getPos(AVLNode *target, int x, int y) {
    return {x + target->position.x, y + target->position.y};
}

AVLNode* AVL::insertAnimation(AVLNode* root, int key) {
    if (root == NULL) return new AVLNode(key);
    if (key < root->data) root->left = insertAnimation(root->left, key);
    else if (key > root->data) root->right = insertAnimation(root->right, key);
    else return root;
    root -> height = 1 + std::max((root->left == NULL ? 0 : root->left->height), (root->right == NULL ? 0 : root->right->height));
    if (root -> balanceFactor() > 1)
        if (key < root->left->data) return rightRotate(root);
        else return leftRightRotate(root);
    if (root -> balanceFactor() < -1)
        if (key > root->right->data) return leftRotate(root);
        else return rightLeftRotate(root);
    return root;
}

AVLNode* AVL::searchAnimation(AVLNode* root, int key) {
    if (root == NULL) return root;
    if (key < root->data) return searchAnimation(root->left, key);
    else if (key > root->data) return searchAnimation(root->right, key);
    return root;
}

AVLNode* AVL::deleteAnimation(AVLNode* root, int key) {
    if (root == NULL) return root;
    if (key < root->data) root->left = deleteAnimation(root->left, key);
    else if (key > root->data) root->right = deleteAnimation(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            AVLNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else *root = *temp;
            delete temp;
        } else {
            AVLNode *temp = root->right;
            while (temp->left != NULL) temp = temp->left;
            root->data = temp->data;
            root->right = deleteAnimation(root->right, temp->data);
        }
    }
    if (root == NULL) return root;
    root -> height = 1 + std::max((root->left == NULL ? 0 : root->left->height), (root->right == NULL ? 0 : root->right->height));
    if (root -> balanceFactor() > 1)
        if (root->left->balanceFactor() >= 0) return rightRotate(root);
        else return leftRightRotate(root);
    if (root -> balanceFactor() < -1)
        if (root->right->balanceFactor() <= 0) return leftRotate(root);
        else return rightLeftRotate(root);
    return root;
}

void AVL::deleteNode(AVLNode* root, AVLNode *target) {
    if (root == target) {
        root = NULL;
        return;
    }
    if (root->left != NULL && root->left == target) {
        AVLNode *temp = root->left;
        root -> left = (temp->left == NULL ? temp->right : temp->left);
        delete temp;
        return;
    }
    if (root->right != NULL && root->right == target) {
        AVLNode *temp = root->right;
        root -> right = (temp->left == NULL ? temp->right : temp->left);
        delete temp;
        return;
    }
}

bool AVL::move(AVLNode *root)
{
    if (root == NULL) return false;
    bool moved = false;
    if (root->position.x != root->targetPosition.x || root->position.y != root->targetPosition.y) {
        root->position = Lerp(root->position, root->targetPosition, 1);
        moved = true;
    }
    if (root->left != NULL) moved |= move(root->left);
    if (root->right != NULL) moved |= move(root->right);
    return moved;
}

bool AVL::moveItr()
{
    bool moved = false;
    for (int i = 0; i < Itr.size(); i++) {
        if (Itr[i].first.x != Itr[i].second.x || Itr[i].first.y != Itr[i].second.y) {
            moved = true;
            Itr[i].first = Lerp(Itr[i].first, Itr[i].second, 1);
        }
        else Itr[i].first = Itr[i].second = {-1, -1};
    }
    return moved;
}

AVLNode* AVL::leftRotate(AVLNode *node) {
    AVLNode *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    temp->height = 1 + std::max((temp->left == NULL ? 0 : temp->left->height), (temp->right == NULL ? 0 : temp->right->height));
    node->height = 1 + std::max((node->left == NULL ? 0 : node->left->height), (node->right == NULL ? 0 : node->right->height));
    return temp;
}

AVLNode* AVL::rightRotate(AVLNode *node) {
    AVLNode *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    temp->height = 1 + std::max((temp->left == NULL ? 0 : temp->left->height), (temp->right == NULL ? 0 : temp->right->height));
    node->height = 1 + std::max((node->left == NULL ? 0 : node->left->height), (node->right == NULL ? 0 : node->right->height));
    return temp;
}

AVLNode* AVL::leftRightRotate(AVLNode *node) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

AVLNode* AVL::rightLeftRotate(AVLNode *node) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}