#include "avl/AVL.hpp"

#include "CodePane.h"
#include "Utility.h"
ColorSet const *AVL::PALETTE = &nodeColorSet;

const std::vector<std::string> AVL::AVLInsert = {
    "Begin",                        // 0
    "search for insert position",   // 1
    "insert node",                  // 2
    "rebalance",                    // 3
    "Case 1: Left rotation",        // 4
    "Case 2: Right rotation",       // 5
    "Case 3: Left-Right rotation",  // 6
    "Case 4: Right-Left rotation",  // 7
    "End",                          // 8
};

const std::vector<std::string> AVL::AVLSearch = {
    "Begin",                               // 9
    "if node.data = value, return node",   // 10
    "if node.data < value, search right",  // 11
    "if node.data > value, search left",   // 12
    "End",                                 // 13
};

const std::vector<std::string> AVL::AVLDelete = {
    "Begin",            // 14
    "search for node",  // 15
    "if node is internal node",
    "   find successor S",    // 16
    "   node.data = S.data",  // 17
    "   delete successor S",  // 18
    "else delete node",       // 19
    "...",
    "End",  // 25
};

const std::vector<std::string> AVL::AVLDelete2 = {
    "Begin",  // 14
    "...",
    "rebalance",                    // 20
    "Case 1: Left rotation",        // 21
    "Case 2: Right rotation",       // 22
    "Case 3: Left-Right rotation",  // 23
    "Case 4: Right-Left rotation",  // 24
    "End",                          // 25
};


const std::vector<std::string> AVL::AVLUpdate = {
    "Begin",            // 26
    "Find the limits of old key",  // 27
    "If new key satisfies the limits, replace old by new",  // 28
    "End",                                 // 29
};

AVL::AVL() : Itr(), changing({ChangeProcedure(-1, -1, NULL), NULL}) {
    loop = 0;
    core = ActionList();
    root = NULL;
    ItrHistory.clear();
    rotateList.clear();
    changeList.clear();
    flag = flagUndo = -1;
}

void AVL::printDebug(AVLNode *root) {
    if (root == NULL) return;
    // std::cout << root->PosInParent << ' ';
    // std::cout << root->value << " " << (root->left ? root->left->value : -1)
            //   << " " << (root->right ? root->right->value : -1) << "\n";
    printDebug(root->left);
    printDebug(root->right);
}

void AVL::setNULLPos(AVLNode *root) {
    if (root == NULL) return;
    root->setPosition((Vector2){800, 90});
    setNULLPos(root->left);
    setNULLPos(root->right);
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

std::vector<AVLNode *> AVL::getNodes(AVLNode *root) {
    std::vector<AVLNode *> nodes;
    if (root == NULL) return nodes;
    if (root->valid == false) return nodes;
    if (root->left != NULL)
        root->left->setTargetedPosition(
            (Vector2){0, root->getTargetedPosition().y + yOFFSET});
    if (root->right != NULL)
        root->right->setTargetedPosition(
            (Vector2){0, root->getTargetedPosition().y + yOFFSET});
    std::vector<AVLNode *> left = getNodes(root->left),
                           right = getNodes(root->right);
    nodes.insert(nodes.end(), left.begin(), left.end());
    nodes.push_back(root);
    nodes.insert(nodes.end(), right.begin(), right.end());
    root->height = 1 + std::max(root->left == NULL ? 0 : root->left->height,
                                root->right == NULL ? 0 : root->right->height);
    root->balance = (root->left == NULL ? 0 : root->left->height) -
                    (root->right == NULL ? 0 : root->right->height);
    root->heightLeft = root->left == NULL ? 0 : root->left->height;
    root->heightRight = root->right == NULL ? 0 : root->right->height;
    root->balanceLeft = root->left == NULL ? 0 : root->left->balance;
    root->balanceRight = root->right == NULL ? 0 : root->right->balance;
    return nodes;
}

void AVL::calcPosition(AVLNode *root) {
    if (root == NULL) return;
    root->setTargetedPosition((Vector2){0, 100});
    std::vector<AVLNode *> nodes = getNodes(root);
    if (nodes.size() == 0) return;
    int mid = nodes.size() / 2;
    nodes[mid]->setTargetedPosition(
        (Vector2){800, nodes[mid]->getTargetedPosition().y});
    for (int i = mid - 1; i >= 0; i--)
        nodes[i]->setTargetedPosition(
            (Vector2){nodes[i + 1]->getTargetedPosition().x - xOFFSET / 2,
                      nodes[i]->getTargetedPosition().y});
    for (int i = mid + 1; i < nodes.size(); i++)
        nodes[i]->setTargetedPosition(
            (Vector2){nodes[i - 1]->getTargetedPosition().x + xOFFSET / 2,
                      nodes[i]->getTargetedPosition().y});
}

std::pair<int, int> AVL::insert(AVLNode *par, AVLNode *&root, int value,
                                ActionList &actions) {
    if (root == NULL) {
        if (par == NULL)
            root = new AVLNode(300, 100, value, par, 0);
        else
            root = new AVLNode(par->getPosition().x, par->getPosition().y,
                               value, par, par->value < value);
        actions.push_back({2, CREATE, root});
        actions.push_back({2, SETLECT, root});
        return {1, 0};
    }
    actions.push_back({1, SETLECT, root});
    if (value < root->value)
        std::tie(root->heightLeft, root->balanceLeft) =
            insert(root, root->left, value, actions);
    else if (value > root->value)
        std::tie(root->heightRight, root->balanceRight) =
            insert(root, root->right, value, actions);
    else
        return {root->height, root->balance};

    actions.push_back({3, SETLECT, root});
    int balance = root->heightLeft - root->heightRight;
    if (balance > 1) {
        if (value < root->left->value) {
            actions.push_back({5, Right, root});
            int hLeft = root->left->heightLeft;
            int hRight =
                std::max(root->left->heightRight, root->heightRight) + 1;
            return {std::max(hLeft, hRight) + 1, hLeft - hRight};
        } else {
            actions.push_back({6, LL, root});
            actions.push_back({6, Right, root});
            int hLeft = std::max(root->left->right->heightLeft,
                                 root->left->heightLeft) +
                        1;
            int hRight =
                std::max(root->left->right->heightRight, root->heightRight) + 1;
            return {std::max(hLeft, hRight) + 1, hLeft - hRight};
        }
        // return {std::max(root->heightLeft, root->heightRight), 1};
    } else if (balance < -1) {
        if (value > root->right->value) {
            actions.push_back({4, Left, root});
            int hLeft = std::max(root->right->heightLeft, root->heightLeft) + 1;
            int hRight = root->right->heightRight;
            return {std::max(hLeft, hRight) + 1, hLeft - hRight};
        } else {
            actions.push_back({7, RR, root});
            actions.push_back({7, Left, root});
            int hLeft =
                std::max(root->right->left->heightLeft, root->heightLeft) + 1;
            int hRight = std::max(root->right->left->heightRight,
                                  root->right->heightRight) +
                         1;
            return {std::max(hLeft, hRight) + 1, hLeft - hRight};
        }
        // return {std::max(root->heightLeft, root->heightRight), -1};
    }
    return {std::max(root->heightLeft, root->heightRight) + 1, balance};
}

void AVL::insert(int value) {
    ActionList actions;
    actions.push_back({0, INIT, NULL});
    insert(NULL, root, value, actions);
    actions.push_back({3, SETLECT, NULL});
    actions.push_back({8, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

void AVL::search(AVLNode *root, int value, ActionList &actions) {
    if (root == NULL) return;
    actions.push_back({root->parent == NULL     ? 9
                       : root->PosInParent == 0 ? 12
                                                : 11,
                       SETLECT, root});
    if (root->value == value) {
        actions.push_back({10, FadeEffect, root});
        return;
    }
    if (value < root->value)
        search(root->left, value, actions);
    else
        search(root->right, value, actions);
}

void AVL::search(int value) {
    ActionList actions;
    actions.push_back({9, INIT, NULL});
    search(root, value, actions);
    actions.push_back({13, SETLECT, NULL});
    actions.push_back({13, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

int AVL::getLeftmost(AVLNode *root) {
    if (root->left == NULL) return root->value;
    return getLeftmost(root->left);
}

std::pair<int, int> AVL::remove(AVLNode *par, AVLNode *root, int value,
                                ActionList &actions) {
    if (root == NULL) return {0, 0};
    actions.push_back({15, SETLECT, root});
    if (value < root->value)
        std::tie(root->heightLeft, root->balanceLeft) =
            remove(root, root->left, value, actions);
    else if (value > root->value)
        std::tie(root->heightRight, root->balanceRight) =
            remove(root, root->right, value, actions);
    else {
        actions.push_back({15, target, root});
        if (root->left == NULL || root->right == NULL) {
            actions.push_back({19, DELETE, root});
            return {std::max(root->left == NULL ? 0 : root->heightLeft,
                             root->right == NULL ? 0 : root->heightRight),
                    0};
        } else {
            int leftmost = getLeftmost(root->right);
            std::tie(root->heightRight, root->balanceLeft) =
                remove(root, root->right, leftmost, actions);
            root->targetValue = leftmost;
            actions.push_back({14, changeValue, root});
            for (int i = actions.size() - 2; i >= 0; i--) {
                if (actions[i].action == target) break;
                std::swap(actions[i], actions[i + 1]);
            }
        }
    }
    actions.push_back({20, SETLECT, root});
    if (root->value == value) actions.push_back({20, untarget, root});
    int balance = root->heightLeft - root->heightRight;
    if (balance > 1) {
        if (root->left->balance >= 0) {
            actions.push_back({22, Right, root});
            int hLeft = std::max(root->left->heightLeft, root->heightLeft) + 1;
            int hRight = root->right->heightRight;
            return {std::max(hLeft, hRight) + 1, hLeft - hRight};
        } else {
            actions.push_back({23, LL, root});
            actions.push_back({23, Right, root});
            int hLeft =
                std::max(root->left->right->heightLeft, root->heightLeft) + 1;
            int hRight = std::max(root->left->right->heightRight,
                                  root->right->heightRight) +
                         1;
            return {std::max(hLeft, hRight) + 1, hLeft - hRight};
        }
        // return {std::max(root->heightLeft, root->heightRight), 1};
    } else if (balance < -1) {
        if (root->right->balance <= 0) {
            actions.push_back({21, Left, root});
            int hLeft = std::max(root->right->heightLeft, root->heightLeft) + 1;
            int hRight = root->right->heightRight;
            return {std::max(hLeft, hRight) + 1, hLeft - hRight};
        } else {
            actions.push_back({24, RR, root});
            actions.push_back({24, Left, root});
            int hLeft =
                std::max(root->right->left->heightLeft, root->heightLeft) + 1;
            int hRight = std::max(root->right->left->heightRight,
                                  root->right->heightRight) +
                         1;
            return {std::max(hLeft, hRight) + 1, hLeft - hRight};
        }
        // return {std::max(root->heightLeft, root->heightRight), -1};
    }
    return {std::max(root->heightLeft, root->heightRight) + 1, balance};
}

#include <cassert>

void AVL::remove(int value) {
    ActionList actions;
    actions.push_back({14, INIT, NULL});
    remove(NULL, root, value, actions);
    actions.push_back({25, CLEAR, NULL});
    for (int i = actions.size() - 1; i >= 0; i--)
        if (actions[i].action == changeValue) {
            assert(i < actions.size() - 1);
            assert(actions[i + 1].action == DELETE);
            actions[i + 1].index = 18;
            for (int j = i; j >= 0; j--)
                if (actions[j].node == actions[i].node && j < i)
                    break;
                else
                    actions[j].index = 16;
            actions[i].index = 17;
            break;
        }
    for (int i = 0; i < actions.size() - 1; i++)
        if (actions[i].action == DELETE) {
            if (actions[i + 1].action == SETLECT) {
                std::swap(actions[i], actions[i + 1]);
                actions[i].index = actions[i + 1].index;
            } else {
                actions.push_back({19, SETLECT, NULL});
                std::swap(actions.back(), actions[i + 1]);
                std::swap(actions[i], actions[i + 1]);
            }
            break;
        }
    actions.push_back({20, SETLECT, NULL});
    std::swap(actions[actions.size() - 1], actions[actions.size() - 2]);
    core.insert(core.end(), actions.begin(), actions.end());
}

bool AVL::Undo(action Action) {
    switch (Action.action) {
        case INIT:
            Itr = ItrAction();
            return true;
        case CLEAR:
            Itr.show = true;
            return true;
        case SETLECT:
            if (ItrHistory.size() &&
                ItrHistory.back().first != Itr.targetedNode) {
                Itr.preNode = Itr.targetedNode;
                Itr.targetedNode = ItrHistory.back().first;
                Itr.animation->setHashAlpha(0);
                Itr.setTarget();
            }
            if (Itr.animation->isCompleted()) ItrHistory.pop_back();
            if (Itr.animation->isCompleted()) return true;
            return false;
        case CREATE:
            Action.node->valid = false;
            calcPosition(root);
            return isCompleted(root);
        case DELETE:
            if (rotateList.size() && rotateList.back() == loop - 1) {
                rotateList.pop_back();
                if (Action.node->parent == NULL)
                    root = Action.node;
                else if (Action.node->PosInParent == 0)
                    Action.node->parent->left = Action.node;
                else
                    Action.node->parent->right = Action.node;
                calcPosition(root);
            }
            return isCompleted(root);
        case target:
            if (Action.node->targeted) Action.node->setUnTarget();
            Action.node->targeted = false;
            return Action.node->isCompletedAlpha();
        case untarget:
            if (!Action.node->targeted) Action.node->setTarget();
            Action.node->targeted = true;
            return Action.node->isCompletedAlpha();
        case changeValue:
            if (changing.second == NULL) {
                Action.node->targetValue = Action.node->value;
                changing = {
                    ChangeProcedure(Action.node->value, changeList.back(),
                                    &Action.node->value),
                    Action.node};
                changeList.pop_back();
            }
            if (changing.first.isCompleted()) {
                changing = {ChangeProcedure(-1, -1, NULL), NULL};
                return true;
            }
            return false;
        case LL:
            if (rotateList.size() && rotateList.back() == loop - 1) {
                rotateList.pop_back();
                AVLNode *leftChild = Action.node->left;
                AVLNode *left_LeftChild = leftChild->left;
                AVLNode *right_left_LeftChild = left_LeftChild->right;

                Action.node->left = left_LeftChild;
                left_LeftChild->parent = Action.node,
                left_LeftChild->PosInParent = 0;
                leftChild->left = right_left_LeftChild;
                if (right_left_LeftChild != NULL)
                    right_left_LeftChild->parent = leftChild,
                    right_left_LeftChild->PosInParent = 0;
                left_LeftChild->right = leftChild;
                leftChild->parent = left_LeftChild, leftChild->PosInParent = 1;
                calcPosition(root);
            }
            return isCompleted(root);
        case RR:
            if (rotateList.size() && rotateList.back() == loop - 1) {
                rotateList.pop_back();
                AVLNode *rightChild = Action.node->right;
                AVLNode *right_RightChild = rightChild->right;
                AVLNode *left_right_RightChild = right_RightChild->left;

                Action.node->right = right_RightChild;
                right_RightChild->parent = Action.node,
                right_RightChild->PosInParent = 1;
                rightChild->right = left_right_RightChild;
                if (left_right_RightChild != NULL)
                    left_right_RightChild->parent = rightChild,
                    left_right_RightChild->PosInParent = 1;
                right_RightChild->left = rightChild;
                rightChild->parent = right_RightChild,
                rightChild->PosInParent = 0;
                calcPosition(root);
            }
            return isCompleted(root);
        case Left:
            if (rotateList.size() && rotateList.back() == loop - 1) {
                rotateList.pop_back();
                AVLNode *par = Action.node->parent;
                AVLNode *rightChild = Action.node->right;

                if (par->parent == NULL)
                    root = Action.node, Action.node->parent = NULL,
                    Action.node->PosInParent = 0;
                else if (par->PosInParent == 0)
                    par->parent->left = Action.node,
                    Action.node->parent = par->parent,
                    Action.node->PosInParent = 0;
                else
                    par->parent->right = Action.node,
                    Action.node->parent = par->parent,
                    Action.node->PosInParent = 1;

                par->left = rightChild;
                if (rightChild != NULL)
                    rightChild->parent = par, rightChild->PosInParent = 0;
                Action.node->right = par, par->parent = Action.node,
                par->PosInParent = 1;
                calcPosition(root);
            }
            return isCompleted(root);
        case Right:
            if (rotateList.size() && rotateList.back() == loop - 1) {
                rotateList.pop_back();
                AVLNode *par = Action.node->parent;
                AVLNode *leftChild = Action.node->left;

                if (par->parent == NULL)
                    root = Action.node, Action.node->parent = NULL,
                    Action.node->PosInParent = 0;
                else if (par->PosInParent == 0)
                    par->parent->left = Action.node,
                    Action.node->parent = par->parent,
                    Action.node->PosInParent = 0;
                else
                    par->parent->right = Action.node,
                    Action.node->parent = par->parent,
                    Action.node->PosInParent = 1;

                par->right = leftChild;
                if (leftChild != NULL)
                    leftChild->parent = par, leftChild->PosInParent = 1;
                Action.node->left = par, par->parent = Action.node,
                par->PosInParent = 0;
                calcPosition(root);
            }
            return isCompleted(root);
        case FadeEffect:
            if (flagUndo == -1)
                flagUndo = 0;
            else if (flagUndo == 1)
                flagUndo = -1;
            return flagUndo;
    }
}

bool AVL::doAction(action Action) {
    switch (Action.action) {
        case INIT:
            Itr.show = true;
            return true;
        case CLEAR:
            // Itr.show = false;
            Itr = ItrAction();
            return true;
        case SETLECT:
            if (ItrHistory.size() == 0 || ItrHistory.back().second != loop) {
                ItrHistory.push_back({Itr.targetedNode, loop});
                Itr.preNode = Itr.targetedNode;
                Itr.targetedNode = Action.node;
                Itr.animation->setHashAlpha(0);
                Itr.setTarget();
            }
            if (Itr.animation->isCompleted()) return true;
            return false;
        case CREATE:
            Action.node->valid = true;
            calcPosition(root);
            return isCompleted(root);
        case DELETE: {
            if (rotateList.size() == 0 || rotateList.back() != loop) {
                rotateList.push_back(loop);
                AVLNode *temp =
                    Action.node->left ? Action.node->left : Action.node->right;
                if (temp != NULL) temp->parent = Action.node->parent;
                if (Action.node->parent == NULL)
                    root = temp;
                else if (Action.node == Action.node->parent->left)
                    Action.node->parent->left = temp;
                else
                    Action.node->parent->right = temp;
                calcPosition(root);
            }
            return isCompleted(root);
        }
        case target:
            if (!Action.node->targeted) Action.node->setTarget();
            Action.node->targeted = true;
            return Action.node->isCompletedAlpha();
        case untarget:
            if (Action.node->targeted) Action.node->setUnTarget();
            Action.node->targeted = false;
            return Action.node->isCompletedAlpha();
        case changeValue:
            if (changing.second == NULL) {
                changeList.push_back(Action.node->value);
                changing = {ChangeProcedure(Action.node->value,
                                            Action.node->targetValue,
                                            &Action.node->value),
                            Action.node};
                Action.node->targetValue = -1;
            }
            if (changing.first.isCompleted()) {
                changing = {ChangeProcedure(-1, -1, NULL), NULL};
                return true;
            }
            return false;
        case LL: {
            if (rotateList.size() == 0 || rotateList.back() != loop) {
                rotateList.push_back(loop);
                AVLNode *leftChild = Action.node->left;
                if (leftChild == nullptr) return false;
                AVLNode *righ_LeftChild = leftChild->right;
                AVLNode *left_Right_LeftChild = righ_LeftChild->left;
                // left rotation on leftChild
                leftChild->right = left_Right_LeftChild;
                if (left_Right_LeftChild != NULL)
                    left_Right_LeftChild->parent = leftChild,
                    left_Right_LeftChild->PosInParent = 1;
                righ_LeftChild->left = leftChild;
                leftChild->parent = righ_LeftChild;
                righ_LeftChild->parent = Action.node,
                righ_LeftChild->PosInParent = 0;
                Action.node->left = righ_LeftChild;
                calcPosition(root);
            }
            return isCompleted(root);
        }
        case RR: {
            if (rotateList.size() == 0 || rotateList.back() != loop) {
                rotateList.push_back(loop);
                AVLNode *rightChild = Action.node->right;
                if (rightChild == nullptr) return false;
                AVLNode *left_RightChild = rightChild->left;
                AVLNode *right_Left_RightChild = left_RightChild->right;
                // right rotation on rightChild
                rightChild->left = right_Left_RightChild;
                if (right_Left_RightChild != NULL)
                    right_Left_RightChild->parent = rightChild,
                    right_Left_RightChild->PosInParent = 0;
                left_RightChild->right = rightChild;
                rightChild->parent = left_RightChild;
                left_RightChild->parent = Action.node,
                left_RightChild->PosInParent = 1;
                Action.node->right = left_RightChild;
                calcPosition(root);
            }
            return isCompleted(root);
        }
        case Left: {
            if (rotateList.size() == 0 || rotateList.back() != loop) {
                rotateList.push_back(loop);
                AVLNode *rightChild = Action.node->right;
                if (rightChild == nullptr) return false;
                AVLNode *Left_RightChild = rightChild->left;

                Action.node->right = Left_RightChild;
                if (Left_RightChild != NULL)
                    Left_RightChild->parent = Action.node,
                    Left_RightChild->PosInParent = 1;
                rightChild->left = Action.node;
                rightChild->parent = Action.node->parent;
                if (Action.node->parent == NULL)
                    root = rightChild;
                else if (Action.node->PosInParent == 0)
                    Action.node->parent->left = rightChild,
                    rightChild->PosInParent = 0;
                else
                    Action.node->parent->right = rightChild,
                    rightChild->PosInParent = 1;
                Action.node->parent = rightChild;
                Action.node->PosInParent = 0;
                calcPosition(root);
            }
            return isCompleted(root);
        }
        case Right: {
            if (rotateList.size() == 0 || rotateList.back() != loop) {
                rotateList.push_back(loop);
                AVLNode *leftChild = Action.node->left;
                if (leftChild == nullptr) return false;
                AVLNode *Right_LeftChild = leftChild->right;

                Action.node->left = Right_LeftChild;
                if (Right_LeftChild != NULL)
                    Right_LeftChild->parent = Action.node,
                    Right_LeftChild->PosInParent = 0;
                leftChild->right = Action.node;
                leftChild->parent = Action.node->parent;
                if (Action.node->parent == NULL)
                    root = leftChild;
                else if (Action.node->PosInParent == 0)
                    Action.node->parent->left = leftChild,
                    leftChild->PosInParent = 0;
                else
                    Action.node->parent->right = leftChild,
                    leftChild->PosInParent = 1;
                Action.node->parent = leftChild;
                Action.node->PosInParent = 1;
                calcPosition(root);
            }
            return isCompleted(root);
        }
        case FadeEffect:
            if (flag == -1)
                flag = 0;
            else if (flag == 1)
                flag = -1;
            return flag;
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
    root->updateAlpha(currTime, rate);
    update(root->left, currTime, rate);
    update(root->right, currTime, rate);
}

void AVL::update(double currTime, double rate) {
    update(root, currTime, rate);
    if (Itr.show) {
        Itr.setTarget();
        Itr.animation->displace(currTime, rate);
    }
    if (loop < core.size() && core[loop].action == FadeEffect && flag == 0) {
        flag = doFadeEffect(root, currTime, rate, core[loop].node).first;
    }
    if (loop > 0 && core[loop - 1].action == FadeEffect && flagUndo == 0) {
        flagUndo =
            doFadeEffect(root, currTime, rate, core[loop - 1].node).first;
    }
    if (changing.second != NULL) changing.first.updateAlpha(currTime, rate);
}

#include <cstring>

void AVL::draw(AVLNode *root) {
    if (root == NULL || root->valid == false) return;
    draw(root->left);
    draw(root->right);
    Color backgroundColor;
    backgroundColor = PALETTE->backgroundNormal;
    DrawCircleV(root->getPosition(), NODE_RADIUS - 3, backgroundColor);
    if (Itr.show && root == Itr.targetedNode) {
        Color tmp = nodeResultColor;
        tmp.a -= Itr.animation->getHashAlpha();
        DrawCircleV(Itr.targetedNode->getPosition(), NODE_RADIUS - 3, tmp);
    }
    if (Itr.show && root == Itr.preNode) {
        Color tmp = nodeResultColor;
        tmp.a -= (255.f - Itr.animation->getHashAlpha());
        DrawCircleV(Itr.preNode->getPosition(), NODE_RADIUS - 3, tmp);
    }
    if (root->targeted || !root->isCompletedAlpha()) {
        backgroundColor = yellowShade;
        backgroundColor.a -= root->alpha;
        DrawCircleV(root->getPosition(), NODE_RADIUS - 3, backgroundColor);
    }
    Color color = greenShade;
    color.a = 255.f - root->getAlpha();
    DrawCircleV(root->getPosition(), NODE_RADIUS - 3, color);
    DrawRing(root->getPosition(), NODE_RADIUS - 3, NODE_RADIUS, 0, 360, 20,
             PALETTE->borderNormal);

    if (changing.second == root) {
        Color colorText = nodeColorSet.textNormal;
        colorText.a -= changing.first.getAlpha();
        char *text =
            new char[std::to_string(changing.first.getNewValue()).length() + 1];
        strcpy(text, std::to_string(changing.first.getNewValue()).c_str());
        Utility::drawText(text, root->getPosition(), Utility::inter30,
                          colorText, 20, Utility::SPACING,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
        colorText = nodeColorSet.textNormal;
        colorText.a -= (255.f - changing.first.getAlpha());
        text =
            new char[std::to_string(changing.first.getOldValue()).length() + 1];
        strcpy(text, std::to_string(changing.first.getOldValue()).c_str());
        Utility::drawText(text, root->getPosition(), Utility::inter30,
                          colorText, 20, Utility::SPACING,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
        return;
    }
    std::string value = std::to_string(root->value);
    char *text = new char[value.length() + 1];
    strcpy(text, value.c_str());
    Utility::drawText(value.c_str(), root->getPosition(), Utility::inter30,
                      PALETTE->textNormal, 20, Utility::SPACING,
                      VerticalAlignment::CENTERED,
                      HorizontalAlignment::CENTERED);
    Color colorText = WHITE;
    if (Itr.show && root == Itr.targetedNode)
        colorText.a -= Itr.animation->getHashAlpha();
    else if (Itr.show && root == Itr.preNode)
        colorText.a -= (255.f - Itr.animation->getHashAlpha());
    else
        colorText = PALETTE->textNormal;
    Utility::drawText(text, root->getPosition(), Utility::inter20, colorText,
                      20, 1, VerticalAlignment::CENTERED,
                      HorizontalAlignment::CENTERED);
    if (root->targeted || !root->isCompletedAlpha()) {
        Color colorText = nodeColorSet.textNormal;
        colorText.a -= root->alpha;
        Utility::drawText(value.c_str(), root->getPosition(), Utility::inter30,
                          colorText, 20, Utility::SPACING,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
    }
    // DrawTextEx(Utility::inter30, text, (Vector2){root->getPosition().x - 12,
    // root->getPosition().y - 12}, 20, 2, WHITE);
}

void AVL::draw() {
    if (!endLoop())
        adjustHighlight(core[loop].index);
    else
        adjustHighlight(-1);
    drawArrow(root);
    draw(root);
    // if (Itr.show)
    //     DrawRing(Itr.animation->getPosition(), NODE_RADIUS, NODE_RADIUS + 3,
    //     0,
    //              360, 20, GBLight::DARK_RED);
}

void AVL::drawArrow(AVLNode *root) {
    if (root == NULL) return;
    if (root->left != NULL && root->left->valid) {
        DrawArrowWithCircles(root->getPosition(), root->left->getPosition(),
                             NODE_RADIUS, PALETTE->borderNormal, 2.5);
        drawArrow(root->left);
    }
    if (root->right != NULL && root->right->valid) {
        DrawArrowWithCircles(root->getPosition(), root->right->getPosition(),
                             NODE_RADIUS, PALETTE->borderNormal, 2.5);
        drawArrow(root->right);
    }
}

void AVL::DrawArrowWithCircles(Vector2 start, Vector2 end, float radius,
                               Color color, float thickness) {
    Vector2 dir = {end.x - start.x, end.y - start.y};
    float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
    dir.x /= length;
    dir.y /= length;
    Vector2 arrowStart = {start.x + radius * dir.x, start.y + radius * dir.y};
    Vector2 arrowEnd = {end.x - radius * dir.x, end.y - radius * dir.y};
    DrawLineEx(arrowStart, arrowEnd, thickness, color);
    float arrowSize = 10.0f;
    Vector2 left = {arrowEnd.x - arrowSize * (dir.x - dir.y),
                    arrowEnd.y - arrowSize * (dir.y + dir.x)};
    Vector2 right = {arrowEnd.x - arrowSize * (dir.x + dir.y),
                     arrowEnd.y - arrowSize * (dir.y - dir.x)};
    DrawTriangle(arrowEnd, left, right, color);
}

bool AVL::completedAllActions() {
    // if (loop < core.size()) std::cout << core[loop].action << std::endl;
    return loop == core.size();
}

bool AVL::completeAnimation() {
    return Itr.animation->isCompleted() & isCompleted(root);
}

bool AVL::reachedEnd() {
    return loop == core.size() || core[loop].action == INIT;
}

bool AVL::reachedStart() { return loop == 0 || core[loop - 1].action == CLEAR; }

void AVL::ClearOperator() {
    while (core.size() > loop) {
        if (core.back().action == CREATE) {
            if (core.back().node->parent == NULL)
                root = NULL;
            else if (core.back().node->parent->left == core.back().node)
                core.back().node->parent->left = NULL;
            else if (core.back().node->parent->right == core.back().node)
                core.back().node->parent->right = NULL;
            delete core.back().node;
        }
        core.pop_back();
    }
}

std::pair<bool, bool> AVL::doFadeEffect(AVLNode *root, double curr,
                                        double Trans, AVLNode *target) {
    if (root == NULL) return {true, false};
    if (root->valid == false) return {true, false};
    if (root == target) return {root->fadeEffect(curr, Trans), true};
    if (target->value < root->value) {
        std::pair<bool, bool> res =
            doFadeEffect(root->left, curr, Trans, target);
        if (res.second == false) return res;
        res.first &= root->fadeEffect(curr, Trans);
        return res;
    }
    if (target->value > root->value) {
        std::pair<bool, bool> res =
            doFadeEffect(root->right, curr, Trans, target);
        if (res.second == false) return res;
        res.first &= root->fadeEffect(curr, Trans);
        return res;
    }
}

AVL::~AVL() {
    core.clear();
    ItrHistory.clear();
    changeList.clear();
    rotateList.clear();
}

int AVL::highlightingRow = -1;
void AVL::adjustHighlight(int index) {
    if (index == -1) {
        highlightingRow = index;
        CodePane::loadCode(AVLInsert);
        CodePane::setHighlight(&highlightingRow);
        return;
    }
    if (index <= 8) {
        CodePane::loadCode(AVLInsert);
        highlightingRow = index;
        CodePane::setHighlight(&highlightingRow);
    } else if (index <= 13) {
        CodePane::loadCode(AVLSearch);
        highlightingRow = index - 9;
        CodePane::setHighlight(&highlightingRow);
    } else {
        if (index <= 19) {
            CodePane::loadCode(AVLDelete);
            highlightingRow = index - 14;
            if (highlightingRow > 1) highlightingRow++;
            CodePane::setHighlight(&highlightingRow);
        } else 
            if (index <= 25) {
            CodePane::loadCode(AVLDelete2);
            highlightingRow = index - 20;
            highlightingRow += 2;
            CodePane::setHighlight(&highlightingRow);
        } else {
            CodePane::loadCode(AVLUpdate);
            highlightingRow = index - 26;
            CodePane::setHighlight(&highlightingRow);
        }
    }
}