#include "AVL.hpp"
#include <mLib/Utility.hpp>

AVL::AVL() : Itr() {
    loop = 0;
    core = ActionList();
    root = NULL;
    ItrHistory.clear(); 
    rotateList.clear();
    changeList.clear();
}

bool AVL::Action(bool isReversed) {
    if (isReversed == 0 && loop == core.size()) return true;
    if (isReversed == 1 && loop == 0) return true;
    if (isReversed == 0 && loop < core.size()) {
        if (doAction(core[loop])) {
            loop++;
            return true;
        }
    } else if (isReversed == 1 && loop > 0) {
        if (Undo(core[loop - 1])) {
            loop--;
            return true;
        }
    }
    return false;
}

std::vector<AVLNode*> AVL::getNodes(AVLNode *root) {
    std::vector<AVLNode*> nodes;
    if (root == NULL) return nodes;
    if (root->left != NULL) root->left->setTargetedPosition((Vector2){0, root->getTargetedPosition().y + yOFFSET});
    if (root->right != NULL) root->right->setTargetedPosition((Vector2){0, root->getTargetedPosition().y + yOFFSET});
    std::vector<AVLNode*> left = getNodes(root->left), right = getNodes(root->right);
    nodes.insert(nodes.end(), left.begin(), left.end());
    nodes.push_back(root);
    nodes.insert(nodes.end(), right.begin(), right.end());
    root->height = 1 + std::max(root->left == NULL ? 0 : root->left->height, root->right == NULL ? 0 : root->right->height);
    root->balance = (root->left == NULL ? 0 : root->left->height) - (root->right == NULL ? 0 : root->right->height);
    root->heightLeft = root->left == NULL ? 0 : root->left->height;
    root->heightRight = root->right == NULL ? 0 : root->right->height;
    root->balanceLeft = root->left == NULL ? 0 : root->left->balance;
    root->balanceRight = root->right == NULL ? 0 : root->right->balance;
    return nodes;
}

void AVL::calcPosition(AVLNode*root) {
    if (root == NULL) return;
    root->setTargetedPosition((Vector2){0, 100});
    std::vector<AVLNode*> nodes = getNodes(root);
    if (nodes.size() == 0) return;
    int mid = nodes.size() / 2;
    nodes[mid]->setTargetedPosition((Vector2){700, nodes[mid]->getTargetedPosition().y});
    for (int i = mid - 1; i >= 0; i--) 
        nodes[i]->setTargetedPosition((Vector2){nodes[i + 1]->getTargetedPosition().x - xOFFSET / 2, nodes[i]->getTargetedPosition().y});
    for (int i = mid + 1; i < nodes.size(); i++)
        nodes[i]->setTargetedPosition((Vector2){nodes[i - 1]->getTargetedPosition().x + xOFFSET / 2, nodes[i]->getTargetedPosition().y});
}

std::pair<int, int> AVL::insert(AVLNode *par, AVLNode *&root, int value, ActionList &actions) {
    if (root == NULL) {
        if (par == NULL) root = new AVLNode(700, 100, value, par);
        else root = new AVLNode(par->getPosition().x, par->getPosition().y, value, par);
        actions.push_back({-1, CREATE, root});
        actions.push_back({-1, SETLECT, root});
        return {1, 0};
    }

    actions.push_back({-1, SETLECT, root});
    if (value < root -> value) std::tie(root -> heightLeft, root -> balanceLeft) = insert(root, root -> left, value, actions);
    else if (value > root -> value) std::tie(root -> heightRight, root -> balanceRight) = insert(root, root -> right, value, actions);
    else return {root -> height, root -> balance};

    actions.push_back({-1, SETLECT, root});
    int balance = root -> heightLeft - root -> heightRight;
    if (balance > 1) {
        if (value < root -> left -> value) {
            actions.push_back({-1, Right, root});
        } else {
            actions.push_back({-1, LL, root});
            actions.push_back({-1, Right, root});
        }
        return {std::max(root -> heightLeft, root -> heightRight), 1};
    }
    else if (balance < -1) {
        if (value > root -> right -> value) {
            actions.push_back({-1, Left, root});
        } else {
            actions.push_back({-1, RR, root});
            actions.push_back({-1, Left, root});
        }
        return {std::max(root -> heightLeft, root -> heightRight), -1};
    }
    return {std::max(root -> heightLeft, root -> heightRight) + 1, balance};
}

void AVL::insert(int value) {
    ActionList actions;
    actions.push_back({-1, INIT, NULL});
    insert(NULL, root, value, actions);
    actions.push_back({-1, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

void AVL::search(AVLNode *root, int value, ActionList &actions) {
    if (root == NULL) return ;
    actions.push_back({-1, SETLECT, root});
    if (root->value == value) return ;
    if (value < root->value) search(root->left, value, actions);
    else search(root->right, value, actions);
}

void AVL::search(int value) {
    ActionList actions;
    actions.push_back({-1, INIT, NULL});
    search(root, value, actions);
    actions.push_back({-1, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

int AVL::getLeftmost(AVLNode *root) {
    if (root->left == NULL) return root->value;
    return getLeftmost(root->left);
}

std::pair<int, int> AVL::remove(AVLNode *par, AVLNode *root, int value, ActionList &actions) {
    if (root == NULL) return {0, 0};
    actions.push_back({-1, SETLECT, root});
    if (value < root->value) std::tie(root->heightLeft, root->balanceLeft) = remove(root, root->left, value, actions);
    else if (value > root->value) std::tie(root->heightRight, root->balanceRight) = remove(root, root->right, value, actions);
    else {
        actions.push_back({-1, target, root});
        if (root->left == NULL || root->right == NULL) {
            actions.push_back({-1, DELETE, root});
            return {std::max(root->left == NULL ? 0 : root->heightLeft, root->right == NULL ? 0 : root->heightRight), 0};
        }
        else {
            int leftmost = getLeftmost(root->right);
            std::tie(root->heightRight, root->balanceLeft) = remove(root, root->right, leftmost, actions);
            root->targetValue = leftmost;
            actions.push_back({-1, changeValue, root});
            for (int i = actions.size() - 2; i >= 0; i--) {
                std::swap(actions[i], actions[i + 1]);
                if (actions[i + 1].action == DELETE) break;
            }
        }
    }
    actions.push_back({-1, SETLECT, root});
    if (actions.size() > 1 && actions[actions.size() - 2].action == DELETE) 
        std::swap(actions[actions.size() - 2], actions[actions.size() - 1]);
    if (root->value == value) actions.push_back({-1, untarget, root});
    int balance = root->heightLeft - root->heightRight;
    if (balance > 1) {
        if (root->left->balance >= 0) {
            actions.push_back({-1, Right, root});
        } else {
            actions.push_back({-1, LL, root});
            actions.push_back({-1, Right, root});
        }
        return {std::max(root->heightLeft, root->heightRight), 1};
    }
    else if (balance < -1) {
        if (root->right->balance <= 0) {
            actions.push_back({-1, Left, root});
        } else {
            actions.push_back({-1, RR, root});
            actions.push_back({-1, Left, root});
        }
        return {std::max(root->heightLeft, root->heightRight), -1};
    }
    return {std::max(root->heightLeft, root->heightRight) + 1, balance};
}

void AVL::remove(int value) {
    ActionList actions;
    actions.push_back({-1, INIT, NULL});
    remove(NULL, root, value, actions);
    actions.push_back({-1, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

bool AVL::Undo(action Action) {
    switch (Action.action)
    {
        case INIT:
            Itr.show = false;
            return true;
        case CLEAR:
            Itr.show = true;
            return true;
        case SETLECT:
            Itr.targetedNode = ItrHistory.back().first;
            Itr.setTarget();
            if (Itr.animation -> isCompleted()) ItrHistory.pop_back();
            if (Itr.animation -> isCompleted()) return true;
            return false;
        case CREATE:
            Action.node->valid = false;
            calcPosition(root);
            return isCompleted(root);
        case DELETE:
            if (rotateList.size() && rotateList.back() == loop - 1) {
                rotateList.pop_back();
                if (Action.node->parent == NULL) root = Action.node;
                else 
                if (Action.node->left == Action.node->parent->left) Action.node->parent->left = Action.node;
                else Action.node->parent->right = Action.node;
            }
            return isCompleted(root);
        case target:
            Action.node->targeted = false;
            return true;
        case untarget:
            Action.node->targeted = true;
            return true;
        case changeValue:
            Action.node->value = changeList.back();
            changeList.pop_back();
            return true;
        case LL:
            if (rotateList.size() && rotateList.back() == loop - 1) {
                rotateList.pop_back();
                AVLNode* temp = Action.node->left;
                Action.node->left = temp->left;
                temp->left->parent = Action.node;
                temp->left = temp->left->right;
                temp->left->parent = temp;
                Action.node->left->right = temp;
                temp->parent = Action.node->left;
                calcPosition(root);
            }
            return isCompleted(root);
        case RR:
            if (rotateList.size() && rotateList.back() == loop - 1) {
                rotateList.pop_back();
                AVLNode* temp = Action.node->right;
                Action.node->right = temp->right;
                temp->right->parent = Action.node;
                temp->right = temp->right->left;
                temp->right->parent = temp;
                Action.node->right->left = temp;
                temp->parent = Action.node->right;
                calcPosition(root);
            }
            return isCompleted(root);
        case Left:
            if (rotateList.size() && rotateList.back() == loop - 1) {
                rotateList.pop_back();
                AVLNode *temp = Action.node->parent;
                Action.node->parent = temp->parent;
                if (temp->parent == NULL) root = Action.node;
                else if (temp == temp->parent->left) temp->parent->left = Action.node;
                else temp->parent->right = Action.node; 
                temp->left = Action.node->right;
                if (Action.node->right != NULL) Action.node->right->parent = temp;
                Action.node->right = temp;
                temp->parent = Action.node;
                calcPosition(root);
            }
            return isCompleted(root);
        case Right:
            if (rotateList.size() && rotateList.back() == loop - 1) {
                rotateList.pop_back();
                AVLNode *temp = Action.node->parent;
                Action.node->parent = temp->parent;
                if (temp->parent == NULL) root = Action.node;
                else if (temp == temp->parent->left) temp->parent->left = Action.node;
                else temp->parent->right = Action.node;
                temp->right = Action.node->left;
                if (Action.node->left != NULL) Action.node->left->parent = temp;
                Action.node->left = temp;
                temp->parent = Action.node;
                calcPosition(root);
            }
            return isCompleted(root);
    }
}

bool AVL::doAction(action Action) {
    switch (Action.action)
    {
        case INIT:
            Itr.show = true;
            return true;
        case CLEAR:
            Itr.show = false;
            return true;
        case SETLECT:
        if (ItrHistory.size() == 0 || ItrHistory.back().second != loop) ItrHistory.push_back({Itr.targetedNode, loop});
        Itr.targetedNode = Action.node;
        Itr.setTarget();
        if (Itr.animation -> isCompleted()) return true;
        return false;
        case CREATE:
            Action.node->valid = true;
            calcPosition(root);
            return isCompleted(root);
        case DELETE: {
            if (rotateList.size() == 0 || rotateList.back() != loop) {
                rotateList.push_back(loop);
                AVLNode *temp = Action.node -> left ? Action.node -> left : Action.node -> right;
                if (temp != NULL) temp->parent = Action.node->parent;
                if (Action.node->parent == NULL) root = temp;
                else if (Action.node == Action.node->parent->left) Action.node->parent->left = temp;
                else Action.node->parent->right = temp;
                calcPosition(root);
            }
            return isCompleted(root);
        }
        case target: 
            Action.node->targeted = true;
            return true;
        case untarget:
            Action.node->targeted = false;
            return true;
        case changeValue:
            changeList.push_back(Action.node->value);
            Action.node->value = Action.node->targetValue;
            Action.node->targetValue = -1;
            return true;
        case LL: {
            if (rotateList.size() == 0 || rotateList.back() != loop) {
                rotateList.push_back(loop);
                AVLNode *leftChild = Action.node->left;
                // left rotation on leftChild
                AVLNode *temp = leftChild->right;
                leftChild->right = temp->left;
                if (temp->left != NULL) temp->left->parent = leftChild;
                temp->left = leftChild;
                leftChild->parent = temp;
                temp->parent = Action.node;
                Action.node->left = temp;
                calcPosition(root);
            }
            return isCompleted(root);
        }
        case RR: {
            if (rotateList.size() == 0 || rotateList.back() != loop) {
                rotateList.push_back(loop);
                AVLNode *rightChild = Action.node->right;
                // right rotation on rightChild
                AVLNode *temp = rightChild->left;
                rightChild->left = temp->right;
                if (temp->right != NULL) temp->right->parent = rightChild;
                temp->right = rightChild;
                rightChild->parent = temp;
                temp->parent = Action.node;
                Action.node->right = temp;
                calcPosition(root);
            }
            return isCompleted(root);
        }
        case Left: {
            if (rotateList.size() == 0 || rotateList.back() != loop) {
                rotateList.push_back(loop);
                AVLNode *temp = Action.node->right;
                Action.node->right = temp->left;
                if (temp->left != NULL) temp->left->parent = Action.node;
                temp->left = Action.node;
                temp->parent = Action.node->parent;
                if (Action.node->parent == NULL) root = temp;
                else if (Action.node == Action.node->parent->left) Action.node->parent->left = temp;
                else Action.node->parent->right = temp;
                Action.node->parent = temp;
                calcPosition(root);
            }
            return isCompleted(root);
        }
        case Right: {
            if (rotateList.size() == 0 || rotateList.back() != loop) {
                rotateList.push_back(loop);
                AVLNode *temp = Action.node->left;
                Action.node->left = temp->right;
                if (temp->right != NULL) temp->right->parent = Action.node;
                temp->right = Action.node;
                temp->parent = Action.node->parent;
                if (Action.node->parent == NULL) root = temp;
                else if (Action.node == Action.node->parent->left) Action.node->parent->left = temp;
                else Action.node->parent->right = temp;
                Action.node->parent = temp;
                calcPosition(root);
            }
            return isCompleted(root);
        }
    }
}

bool AVL::isCompleted(AVLNode *root) {
    if (root == NULL) return true;
    bool completed = true;
    completed &= root->isCompleted();
    completed &= isCompleted(root->left);
    completed &= isCompleted(root->right);
    return completed;
}

void AVL::update(AVLNode *root, double currTime, double rate) {
    if (root == NULL) return;
    root->displace(currTime, rate);
    update(root->left, currTime, rate);
    update(root->right, currTime, rate);
}

void AVL::update(double currTime, double rate) {
    update(root, currTime, rate);
    if (Itr.show) {
        Itr.setTarget();
        Itr.animation->displace(currTime, rate);
    }
}

#include <cstring>

void AVL::draw(AVLNode*root) {
    if (root == NULL) return;
    draw(root->left);
    draw(root->right);
    DrawCircleV(root->getPosition(), NODE_RADIUS, root->targeted ? ORANGE : BLUE);
    std::string value = std::to_string(root->value);
    char *text = new char[value.length() + 1];
    strcpy(text, value.c_str());
    DrawTextEx(mLib::mFont, text, (Vector2){root->getPosition().x - 10, root->getPosition().y - 10}, 20, 2, WHITE);
}

void AVL::draw() {
    //if (!endLoop()) mLib::DrawTextTrie(core[loop].index);
    drawArrow(root);
    draw(root);
    if (Itr.show) DrawRing(Itr.animation->getPosition(), NODE_RADIUS, NODE_RADIUS + 5, 0, 360, 20, GREEN);
}

void AVL::drawArrow(AVLNode* root) {
    if (root == NULL) return;
    if (root->left != NULL && root->left->valid) {
        DrawArrowWithCircles(root->getPosition(), root->left->getPosition(), NODE_RADIUS, RED, 2);
        drawArrow(root->left);
    }
    if (root->right != NULL && root->right->valid) {
        DrawArrowWithCircles(root->getPosition(), root->right->getPosition(), NODE_RADIUS, RED, 2);
        drawArrow(root->right);
    }
}

void AVL::DrawArrowWithCircles(Vector2 start, Vector2 end, float radius, Color color, float thickness) {
    Vector2 dir = { end.x - start.x, end.y - start.y };
    float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
    dir.x /= length;
    dir.y /= length;
    Vector2 arrowStart = { start.x + radius * dir.x, start.y + radius * dir.y };
    Vector2 arrowEnd = { end.x - radius * dir.x, end.y - radius * dir.y };
    DrawLineEx(arrowStart, arrowEnd, thickness, color);
    float arrowSize = 20.0f;
    Vector2 left = { arrowEnd.x - arrowSize * (dir.x - dir.y), arrowEnd.y - arrowSize * (dir.y + dir.x) };
    Vector2 right = { arrowEnd.x - arrowSize * (dir.x + dir.y), arrowEnd.y - arrowSize * (dir.y - dir.x) };
    DrawTriangle(arrowEnd, left, right, color);
}

bool AVL::completedAllActions() {
    return loop == core.size();
}

bool AVL::completeAnimation() {
    return Itr.animation->isCompleted() & isCompleted(root);
}

bool AVL::reachedEnd() {
    return loop == core.size() || core[loop].action == INIT;
}

bool AVL::reachedStart() {
    return loop == 0 || core[loop - 1].action == CLEAR;
}

void AVL::ClearOperator() {
    while (core.size() > loop) {
        if (core.back().action == CREATE) {
            if (core.back().node->parent->left == core.back().node) core.back().node->parent->left = NULL;
            else core.back().node->parent->right = NULL;
            delete core.back().node;
        }
        core.pop_back();
    }
}

AVL::~AVL() {
    core.clear();
    ItrHistory.clear();
    changeList.clear();
    rotateList.clear();
}