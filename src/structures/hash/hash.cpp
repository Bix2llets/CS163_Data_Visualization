#include "hash/hash.h"

#include "CodePane.h"
#include "Utility.h"
ColorSet const *Hash::PALETTE = &nodeColorSet;
Hash::Hash(int _m = 10)
    : Itr(), m(_m), changing({ChangeProcedure(-1, -1, NULL), NULL}) {
    loop = 0;
    core = ActionList();
    root.clear();
    hashNode *node;  //= new hashNode(100, 350, -1);
    // root.push_back(node);
    int numRow = m / 15 + 1;
    for (int i = 0; i < m; i++) {
        int X = i / 15, Y = i % 15;  /// location in matrix
        node = new hashNode(100 + xOFFSET * Y, 400 + (X - numRow / 2) * yOFFSET,
                            -1);
        root.push_back(node);
    }
    ItrHistory.clear();
    changeList.clear();
    flag = flagUndo = -1;
    // std::cout << "done create\n";
}

void Hash::printTable() {
    for (int i = 0; i < m; i++) {
        // std::cout << root[i]->getPosition().x << ' '<<
        // root[i]->getPosition().y << " "; std::cout << root[i]->targeted << '
        // ' << root[i]->value << ' ' << root[i]->targetValue << "\n";
    }
    // std::cout << "\n";
}

bool Hash::Action(bool isReversed) {
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

void Hash::insert(int value) {
    if (m == 0) return;
    ActionList actions;
    int index = value % m;
    actions.push_back({0, INIT, NULL});
    actions.push_back({1, SETLECT, root[index]});
    while (root[index]->value != -1) {
        index = (index + 1) % m;
        actions.push_back({2, SETLECT, root[index]});
        if (index == value % m) break;
    }
    actions.push_back({2, SETLECT, NULL});
    if (root[index]->value == -1) {
        root[index]->targetValue = value;
        actions.push_back({3, target, root[index]});
        actions.push_back({3, changeValue, root[index]});
        actions.push_back({3, untarget, root[index]});
    }
    actions.push_back({4, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

void Hash::search(int value) {
    if (m == 0) return;
    ActionList actions;
    actions.push_back({5, INIT, NULL});
    int index = value % m;
    actions.push_back({6, SETLECT, root[index]});
    while (root[index]->value != value && root[index]->value != -1) {
        index = (index + 1) % m;
        actions.push_back({7, SETLECT, root[index]});
        if (index == value % m) break;
    }
    actions.push_back({7, SETLECT, NULL});
    if (root[index]->value == value) {
        actions.push_back({8, FadeEffect, root[index]});
    }
    actions.push_back({9, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

void Hash::remove(int value) {
    if (m == 0) return;
    ActionList actions;
    actions.push_back({10, INIT, NULL});
    int index = value % m;
    actions.push_back({11, SETLECT, root[index]});
    while (root[index]->value != value && root[index]->value != -1) {
        index = (index + 1) % m;
        actions.push_back({12, SETLECT, root[index]});
        if (index == value % m) break;
    }
    actions.push_back({12, SETLECT, NULL});
    if (root[index]->value == value) {
        actions.push_back({13, target, root[index]});
        root[index]->targetValue = -1;
        actions.push_back({13, changeValue, root[index]});
        actions.push_back({13, untarget, root[index]});
    }
    actions.push_back({14, CLEAR, NULL});
    core.insert(core.end(), actions.begin(), actions.end());
}

bool Hash::Undo(action Action) {
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
        case target:
            Action.node->targeted = false;
            return true;
        case untarget:
            Action.node->targeted = true;
            return true;
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
        case FadeEffect:
            if (flagUndo == -1)
                flagUndo = 0;
            else if (flagUndo == 1)
                flagUndo = -1;
            return flagUndo;
    }
}

bool Hash::doAction(action Action) {
    switch (Action.action) {
        case INIT:
            Itr.show = true;
            return true;
        case CLEAR:
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
        case target:
            Action.node->targeted = true;
            return true;
        case untarget:
            Action.node->targeted = false;
            return true;
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
                // std::cout << Action.node->value << ' ' <<
                // changing.first.getNewValue() << std::endl;
                changing = {ChangeProcedure(-1, -1, NULL), NULL};
                return true;
            }
            return false;
        case FadeEffect:
            if (flag == -1)
                flag = 0;
            else if (flag == 1)
                flag = -1;
            return flag;
    }
}

std::pair<bool, bool> Hash::doFadeEffect(double curr, double Trans,
                                         hashNode *target) {
    for (int i = 0; i < m; i++)
        if (root[i] == target) return {root[i]->fadeEffect(curr, Trans), true};
}

void Hash::update(double currTime, double rate) {
    for (int i = 0; i < m; i++) {
        root[i]->displace(currTime, rate);
    }
    if (Itr.show) {
        Itr.setTarget();
        Itr.animation->displace(currTime, rate);
    }
    if (loop < core.size() && core[loop].action == FadeEffect && flag == 0) {
        // std::cout << "fade effect\n";
        flag = doFadeEffect(currTime, rate, core[loop].node).first;
    }
    if (loop > 0 && core[loop - 1].action == FadeEffect && flagUndo == 0) {
        flagUndo = doFadeEffect(currTime, rate, core[loop - 1].node).first;
    }
    if (changing.second != NULL) changing.first.updateAlpha(currTime, rate);
}

#include <cstring>

void Hash::draw(hashNode *node) {
    if (node == NULL) return;
    DrawCircleV(node->getPosition(), NODE_RADIUS - 3,
                node->targeted ? PALETTE->backgroundHighlight
                               : PALETTE->backgroundNormal);
    if (Itr.show && node == Itr.targetedNode) {
        Color tmp = nodeResultColor;
        tmp.a -= Itr.animation->getHashAlpha();
        DrawCircleV(Itr.targetedNode->getPosition(), NODE_RADIUS - 3, tmp);
    }
    if (Itr.show && node == Itr.preNode) {
        Color tmp = nodeResultColor;
        tmp.a -= (255.f - Itr.animation->getHashAlpha());
        DrawCircleV(Itr.preNode->getPosition(), NODE_RADIUS - 3, tmp);
    }
    Color tmp = greenShade;
    tmp.a -= node->getAlpha();
    DrawCircleV(node->getPosition(), NODE_RADIUS - 3, tmp);
    DrawRing(node->getPosition(), NODE_RADIUS - 3, NODE_RADIUS, 0, 360, 20,
             PALETTE->borderNormal);
    if (changing.second == node) {
        Color colorText = PALETTE->textNormal;
        colorText.a -= (255.f - changing.first.getAlpha());
        char *text =
            new char[std::to_string(changing.first.getOldValue()).length() + 1];
        strcpy(text, std::to_string(changing.first.getOldValue()).c_str());
        if (changing.first.getOldValue() == -1) strcpy(text, "null");
        Utility::drawText(text, node->getPosition(), Utility::inter20,
                          colorText, 20, 1, VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
        colorText = PALETTE->textNormal;
        colorText.a -= changing.first.getAlpha();
        text =
            new char[std::to_string(changing.first.getNewValue()).length() + 1];
        strcpy(text, std::to_string(changing.first.getNewValue()).c_str());
        if (changing.first.getNewValue() == -1) strcpy(text, "null");
        Utility::drawText(text, node->getPosition(), Utility::inter20,
                          colorText, 20, 1, VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
        return;
    }
    std::string value = std::to_string(node->value);
    if (node->value == -1) value = "null";
    char *text = new char[value.length() + 1];
    strcpy(text, value.c_str());
    Utility::drawText(text, node->getPosition(), Utility::inter20,
                      PALETTE->textNormal, 20, 1, VerticalAlignment::CENTERED,
                      HorizontalAlignment::CENTERED);
    Color colorText = PALETTE->textNormal;
    if (Itr.show && node == Itr.targetedNode)
        colorText.a -= Itr.animation->getHashAlpha();
    else if (Itr.show && node == Itr.preNode)
        colorText.a -= (255.f - Itr.animation->getHashAlpha());
    else
        colorText = PALETTE->textNormal;
    Utility::drawText(text, node->getPosition(), Utility::inter20, colorText,
                      20, 1, VerticalAlignment::CENTERED,
                      HorizontalAlignment::CENTERED);
}

void Hash::draw() {
    if (!endLoop())
        adjustHighlight(core[loop].index);
    else
        adjustHighlight(-1);
    for (int i = 0; i < m; i++) {
        Utility::drawText(std::to_string(i).c_str(),
                          Vector2Add(root[i]->getPosition(), Vector2{0, -50}),
                          Utility::inter20, PALETTE->textNormal, 20, 1,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
        draw(root[i]);
    }
}

void Hash::DrawArrowWithCircles(Vector2 start, Vector2 end, float radius,
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

bool Hash::completedAllActions() { return loop == core.size(); }

bool Hash::completeAnimation() {
    bool f = 1;
    for (int i = 0; i < m; i++) {
        f &= root[i]->isCompleted();
    }
    return Itr.animation->isCompleted() & f;
}

bool Hash::reachedEnd() {
    return loop == core.size() || core[loop].action == INIT;
}

bool Hash::reachedStart() {
    return loop == 0 || core[loop - 1].action == CLEAR;
}

void Hash::ClearOperator() {
    while (core.size() > loop) {
        core.pop_back();
    }
}

Hash::~Hash() {
    core.clear();
    ItrHistory.clear();
    changeList.clear();
    root.clear();
}

const std::vector<std::string> Hash::hashInsert = {
    "Begin",                                 // 0
    "i = v % m",                             // 1
    "while a[i]->v != -1, i = (i + 1) % m",  // 2
    "if a[i]->v = -1, a[i]->v = v",          // 3
    "End",                                   // 4
};

const std::vector<std::string> Hash::hashSearch = {
    "Begin",                                         // 5
    "i = v % m",                                     // 6
    "while a[i]->v != (v and -1), i = (i + 1) % m",  // 7
    "if a[i]->v == v, return i",                     // 8
    "End",                                           // 9
};

const std::vector<std::string> Hash::hashDelete = {
    "Begin",                                         // 10
    "i = v % m",                                     // 11
    "while a[i]->v != (v and -1), i = (i + 1) % m",  // 12
    "if a[i]->v == v, a[i]->v = -1",                 // 13
    "End",                                           // 14
};
const std::vector<std::string> Hash::hashUp = {
    "Begin",            // 15
    "target a[Pos]",    // 16
    "a[Pos]->v = v",    // 17
    "untarget a[Pos]",  // 18
    "End",              // 19
};
int Hash::highlightingRow = -1;
void Hash::adjustHighlight(int index) {
    if (index == -1) {
        highlightingRow = index;
        CodePane::loadCode(hashInsert);
        CodePane::setHighlight(&highlightingRow);
        return;
    }
    if (index <= 4) {
        highlightingRow = index;
        CodePane::loadCode(hashInsert);
        CodePane::setHighlight(&highlightingRow);
    } else if (index <= 9) {
        highlightingRow = index - 5;
        CodePane::loadCode(hashSearch);
        CodePane::setHighlight(&highlightingRow);
    } else if (index <= 14) {
        highlightingRow = index - 10;
        CodePane::loadCode(hashDelete);
        CodePane::setHighlight(&highlightingRow);
    } else {
        highlightingRow = index - 15;
        CodePane::loadCode(hashUp);
        CodePane::setHighlight(&highlightingRow);
    }
}