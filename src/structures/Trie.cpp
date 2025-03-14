#include "Trie.hpp"
#include <mLib/Utility.hpp>

Trie::Trie() : Itr() {
    loop = 0;
    core = ActionList();
    root = new TrieNode(700, 100, '\0', NULL);
    ItrHistory.clear();
}

bool Trie::Action(bool isReversed) {
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

Vector2 Trie::calcPosition(TrieNode *root) {
    Vector2 width = {0, 0};
    std::vector<Vector2> widthList;
    std::vector<TrieNode*> queue;
    for (auto &child : root->children) 
        if (child.second->valid) {
            queue.push_back(child.second);
            widthList.push_back(calcPosition(child.second));
        }
    if (queue.size() == 0) return width;
    int mid1, mid2;
    if (queue.size() % 2 == 0) {
        mid1 = queue.size() / 2 - 1;
        mid2 = queue.size() / 2;
        queue[mid1]->setTargetedPosition((Vector2){- (widthList[mid1].y + xOFFSET / 2), yOFFSET});
        queue[mid2]->setTargetedPosition((Vector2){widthList[mid2].x + xOFFSET / 2, yOFFSET});
        width.x = widthList[mid1].x + widthList[mid1].y + xOFFSET / 2;
        width.y = widthList[mid2].x + widthList[mid2].y + xOFFSET / 2;
    } else {
        mid1 = queue.size() / 2;
        mid2 = queue.size() / 2;
        queue[mid1]->setTargetedPosition((Vector2){0, yOFFSET});
        width = widthList[mid1];
    }
    for (int i = mid1 - 1; i >= 0; i--) {
        queue[i]->setTargetedPosition((Vector2){- (width.x + widthList[i].y + xOFFSET), yOFFSET});
        width.x += widthList[i].x + widthList[i].y + xOFFSET;
    }
    for (int i = mid2 + 1; i < queue.size(); i++) {
        queue[i]->setTargetedPosition((Vector2){width.y + widthList[i].x + xOFFSET, yOFFSET});
        width.y += widthList[i].x + widthList[i].y + xOFFSET;
    }

    return width;
}

void Trie::insert(std::string word) {
    ActionList actions;
    TrieNode *current = root;
    actions.push_back({0, INIT, current});
    if (current == NULL) exit(1);
    actions.push_back({1, SETLECT, current});
    for (int i = 0; i < word.size(); i++) {
        if (current->children.find(word[i]) == current->children.end()) {
            current->children[word[i]] = new TrieNode(current->getPosition().x, current->getPosition().y, word[i], current);
            actions.push_back({2, CREATE, current->children[word[i]]});
        }
        current = current->children[word[i]];
        actions.push_back({3, SETLECT, current});
    }
    actions.push_back({4, SETEND, current});
    actions.push_back({5, CLEAR, current});
    core.insert(core.end(), actions.begin(), actions.end());
}

void Trie::search(std::string word) {
    ActionList actions;
    TrieNode *current = root;
    actions.push_back({6, INIT, current});
    actions.push_back({7, SETLECT, current});
    for (int i = 0; i < word.size(); i++) {
        if (current->children.find(word[i]) == current->children.end()) {
            actions.push_back({8, CLEAR, current});
            core.insert(core.end(), actions.begin(), actions.end());
            return ;
        }
        current = current->children[word[i]];
        actions.push_back({9, SETLECT, current});
    }
    actions.push_back({10, CLEAR, current});
    core.insert(core.end(), actions.begin(), actions.end());
}

void Trie::remove(std::string word) {
    ActionList actions;
    TrieNode *current = root;
    actions.push_back({11, INIT, current});
    actions.push_back({12, SETLECT, current});
    for (int i = 0; i < word.size(); i++) {
        if (current->children.find(word[i]) == current->children.end()) {
            actions.push_back({13, CLEAR, current});
            core.insert(core.end(), actions.begin(), actions.end());
            return ;
        }
        current = current->children[word[i]];
        actions.push_back({14, SETLECT, current});
    }
    actions.push_back({15, UNSETEND, current});
    bool flag = current->isEndOfWord & current->children.size() == 0;
    while (flag && current != root) {
        TrieNode *parent = current->parent;
        actions.push_back({16, SETLECT, parent});
        actions.push_back({17, DELETE, current});
        current = parent;
        if (current->children.size() > 1) flag = false;
    }
    actions.push_back({18, CLEAR, current});
    core.insert(core.end(), actions.begin(), actions.end());
}

bool Trie::Undo(action Action) {
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
            APosition(root);
            return isCompleted(root);
        case DELETE:
            Action.node->parent->children[Action.node->character] = Action.node;
            calcPosition(root);
            APosition(root);
            return isCompleted(root);
        case SETEND:
            Action.node->isEndOfWord = false;
            return true;
        case UNSETEND:
            Action.node->isEndOfWord = true;
            return true;
    }
}

bool Trie::doAction(action Action) {
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
            APosition(root);
            return isCompleted(root);
        case DELETE:
            Action.node->parent->children.erase(Action.node->character);
            calcPosition(root);
            APosition(root);
            return isCompleted(root);
        case SETEND:
            Action.node->isEndOfWord = true;
            return true;
        case UNSETEND:
            Action.node->isEndOfWord = false;
            return true;
    }
}

void Trie::APosition(TrieNode *root) {
    if (root == NULL) return;
    for (auto &child : root->children) {
        if (child.second->valid == 0) child.second->setTargetedPosition(root->getTargetedPosition());
        else child.second->setTargetedPosition(child.second->getTargetedPosition() + root->getTargetedPosition());
        APosition(child.second);
    }
}

bool Trie::isCompleted(TrieNode *root) {
    if (root == NULL) return true;
    bool completed = true;
    completed &= root->isCompleted();
    for (auto &child : root->children) completed &= isCompleted(child.second);
    return completed;
}

void Trie::update(TrieNode *root, double currTime, double rate) {
    if (root == NULL) return;
    root->displace(currTime, rate);
    for (auto &child : root->children) update(child.second, currTime, rate);
}

void Trie::update(double currTime, double rate) {
    update(root, currTime, rate);
    if (Itr.show) {
        Itr.setTarget();
        Itr.animation->displace(currTime, rate);
    }
}

void Trie::draw(TrieNode *root) {
    if (root == NULL) return;
    for (auto &child : root->children) draw(child.second);
    DrawCircleV(root->getPosition(), NODE_RADIUS, root->isEndOfWord ? ORANGE : BLUE);
    char str[2] = {root->character, '\0'};
    DrawTextEx(mLib::mFont, str, (Vector2){root->getPosition().x - 10, root->getPosition().y - 10}, 20, 2, WHITE);
}

void Trie::draw() {
    if (!endLoop()) mLib::DrawTextTrie(core[loop].index);
    drawArrow(root);
    draw(root);
    if (Itr.show) DrawRing(Itr.animation->getPosition(), NODE_RADIUS, NODE_RADIUS + 5, 0, 360, 20, GREEN);
}

void Trie::drawArrow(TrieNode* root) {
    if (root == NULL) return;
    for (auto &child : root->children) 
        if (child.second->valid) {
            DrawArrowWithCircles(root->getPosition(), child.second->getPosition(), NODE_RADIUS, RED, 2);
            drawArrow(child.second);
        }
}

void Trie::DrawArrowWithCircles(Vector2 start, Vector2 end, float radius, Color color, float thickness) {
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

bool Trie::completedAllActions() {
    return loop == core.size();
}

bool Trie::completeAnimation() {
    return Itr.animation->isCompleted() & isCompleted(root);
}

bool Trie::reachedEnd() {
    return loop == core.size() || core[loop].action == INIT;
}

bool Trie::reachedStart() {
    return loop == 0 || core[loop - 1].action == CLEAR;
}

void Trie::ClearOperator() {
    while (core.size() > loop) {
        if (core.back().action == CREATE) {
            core.back().node->parent->children.erase(core.back().node->character);
            delete core.back().node;
        }
        core.pop_back();
    }
}

Trie::~Trie() {
    core.clear();
    ItrHistory.clear();
}