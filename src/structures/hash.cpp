#include "hash.hpp"
#include <mLib/Utility.hpp>

hash::hash(int _m = 10) : Itr(), m(_m) {
    loop = 0;
    core = ActionList();
    root.clear();
    hashNode *node = new hashNode(100, 400, -1);
    root.push_back(node);
    for (int i = 1; i < m; i++) {
        node = new hashNode(root[i - 1]->getPosition().x + xOFFSET, root[i - 1]->getPosition().y, -1);
        root.push_back(node);
    }
    ItrHistory.clear(); 
    changeList.clear();
    flag = flagUndo = -1;
}

void hash::printTable() {
    for (int i = 0; i < m; i ++) {
        std::cout << root[i]->getPosition().x << ' '<< root[i]->getPosition().y << " ";
        std::cout << root[i]->targeted << ' ' << root[i]->value << ' ' << root[i]->targetValue << "\n";

    }
    std::cout << "\n";
}

bool hash::Action(bool isReversed) {
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

void hash::insert(int value) {
    ActionList actions;
    int index = value % m;
    actions.push_back({0, INIT, NULL});
    actions.push_back({1, SETLECT, root[index]});
    while (root[index]->value != -1) {
        index = (index + 1) % m;
        actions.push_back({2, SETLECT, root[index]});
        if (index == value % m) break;
    }
    if (root[index]->value == -1) {
        root[index]->targetValue = value;
        actions.push_back({3, target, root[index]});
        actions.push_back({3, changeValue, root[index]});
        actions.push_back({3, untarget, root[index]});
    }
    actions.push_back({4, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

void hash::search(int value) {
    ActionList actions;
    actions.push_back({5, INIT, NULL});
    int index = value % m;
    actions.push_back({6, SETLECT, root[index]});
    while (root[index]->value != value) {
        index = (index + 1) % m;
        actions.push_back({7, SETLECT, root[index]});
        if (index == value % m) break;
    }
    if (root[index]->value == value) {
        actions.push_back({8, FadeEffect, root[index]});
    }
    actions.push_back({9, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

void hash::remove(int value) {
    ActionList actions;
    actions.push_back({10, INIT, NULL});
    int index = value % m;
    actions.push_back({11, SETLECT, root[index]});
    while (root[index]->value != value && root[index]->value != -1) {
        index = (index + 1) % m;
        actions.push_back({12, SETLECT, root[index]});
        if (index == value % m) break;
    }
    if (root[index]->value == value) {
        actions.push_back({13, target, root[index]});
        root[index]->targetValue = -1;
        actions.push_back({13, changeValue, root[index]});
        actions.push_back({13, untarget, root[index]});
    }
    actions.push_back({14, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

bool hash::Undo(action Action) {
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
        case FadeEffect:
            if (flagUndo == -1) flagUndo = 0;
            else if (flagUndo == 1) flagUndo = -1;
            return flagUndo;
    }
}

bool hash::doAction(action Action) {
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
        case FadeEffect:
            if (flag == -1) flag = 0;
            else if (flag == 1) flag = -1;
            return flag;
    }
}

std::pair<bool, bool> hash::doFadeEffect(double curr, double Trans, hashNode *target) {
    for (int i = 0; i < m; i++) 
        if (root[i] == target) return {root[i]->fadeEffect(curr, Trans), true};
}

void hash::update(double currTime, double rate) {
    if (Itr.show) {
        Itr.setTarget();
        Itr.animation->displace(currTime, rate);
    }
    if (loop < core.size() && core[loop].action == FadeEffect && flag == 0) {
        std::cout << "fade effect\n";
        flag = doFadeEffect(currTime, rate, core[loop].node).first;
    }
    if (loop > 0 && core[loop - 1].action == FadeEffect && flagUndo == 0) {
        flagUndo = doFadeEffect(currTime, rate, core[loop - 1].node).first;
    }
}

#include <cstring>

void hash::draw(hashNode* node) {
    if (node == NULL) return;
    DrawCircleV(node->getPosition(), NODE_RADIUS - 5, node->targeted ? ORANGE : (Color) {0, 160, 216, node->getAlpha()});
    DrawRing(node->getPosition(), NODE_RADIUS - 5, NODE_RADIUS, 0, 360, 20, BLUE);
    std::string value = std::to_string(node->value);
    if (node->value == -1) value = "null";
    char *text = new char[value.length() + 1];
    strcpy(text, value.c_str());
    DrawTextEx(mLib::mFont, text, (Vector2){node->getPosition().x - 12, node->getPosition().y - 12}, 20, 2, WHITE);
}

void hash::draw() {
    if (!endLoop()) mLib::DrawTextHash(core[loop].index);
    else mLib::DrawTextHash(-1);
    for (int i = 0; i < m - 1; i ++) DrawArrowWithCircles(root[i]->getPosition(), root[i + 1]->getPosition(), NODE_RADIUS, (Color) {0, 160, 216, 241}, 2.5);
    for (int i = 0; i < m; i++) {
        DrawTextEx(mLib::mFont, std::to_string(i).c_str(), (Vector2){root[i]->getPosition().x - 10, root[i]->getPosition().y - 50}, 20, 2, WHITE);
        draw(root[i]);
    }
    if (Itr.show) DrawRing(Itr.animation->getPosition(), NODE_RADIUS, NODE_RADIUS + 5, 0, 360, 20, (Color) {255, 116, 109, 255});
}

void hash::DrawArrowWithCircles(Vector2 start, Vector2 end, float radius, Color color, float thickness) {
    Vector2 dir = { end.x - start.x, end.y - start.y };
    float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
    dir.x /= length;
    dir.y /= length;
    Vector2 arrowStart = { start.x + radius * dir.x, start.y + radius * dir.y };
    Vector2 arrowEnd = { end.x - radius * dir.x, end.y - radius * dir.y };
    DrawLineEx(arrowStart, arrowEnd, thickness, color);
    float arrowSize = 10.0f;
    Vector2 left = { arrowEnd.x - arrowSize * (dir.x - dir.y), arrowEnd.y - arrowSize * (dir.y + dir.x) };
    Vector2 right = { arrowEnd.x - arrowSize * (dir.x + dir.y), arrowEnd.y - arrowSize * (dir.y - dir.x) };
    DrawTriangle(arrowEnd, left, right, color);
}

bool hash::completedAllActions() {
    return loop == core.size();
}

bool hash::completeAnimation() {
    return Itr.animation->isCompleted();
}

bool hash::reachedEnd() {
    return loop == core.size() || core[loop].action == INIT;
}

bool hash::reachedStart() {
    return loop == 0 || core[loop - 1].action == CLEAR;
}

void hash::ClearOperator() {
    while (core.size() > loop) {
        core.pop_back();
    }
}

hash::~hash() {
    core.clear();
    ItrHistory.clear();
    changeList.clear();
    root.clear();
}