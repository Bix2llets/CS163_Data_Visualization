#ifndef hash_HPP
#define hash_HPP

#include <cmath>
#include <iostream>
#include <mLib/changeProcedure.hpp>
#include <queue>
#include <string>
#include <vector>

#include "colorPalette.h"
#include "hashNode.hpp"
#include "raylib.h"
class Hash {
   private:
    enum hashAction {
        INIT,
        CLEAR,
        SETLECT,
        target,
        untarget,
        changeValue,
        FadeEffect,
    };

    struct ItrAction {
        Animation *animation;
        bool show;
        hashNode *targetedNode, *preNode;
        void setTarget() {
            if (targetedNode == NULL)
                animation->setTargetedPosition((Vector2){0, 0});
            else
                animation->setTargetedPosition(
                    targetedNode->getTargetedPosition());
        }
        ItrAction() {
            animation = new Animation(0, 0);
            targetedNode = preNode = NULL;
            show = false;
        }
    };

    struct action {
        int index;
        hashAction action;
        hashNode *node;
    };

    typedef std::vector<action> ActionList;

   private:
    float xOFFSET = 100, yOFFSET = 130, NODE_RADIUS = 30;
    int m, flag, flagUndo;
    std::vector<hashNode *> root;

   public:
    static ColorSet const *PALETTE;
    static int highlightingRow;


    int getSize() { return m; }
    void updatePos_Key(int pos, int key) {
        if (pos < 0 || pos >= m) return;
        ActionList actions;
        actions.push_back({15, INIT, NULL});
        actions.push_back({16, target, root[pos]});
        root[pos]->targetValue = key;
        actions.push_back({17, changeValue, root[pos]});
        actions.push_back({18, untarget, root[pos]});
        actions.push_back({19, CLEAR, NULL});
        core.insert(core.end(), actions.begin(), actions.end());
    }
    void printTable();
    Hash(int _m);
    bool Action(bool isReversed);
    bool doAction(action Action);
    bool Undo(action Action);
    void insert(int value);
    void search(int value);
    void remove(int value);
    void draw();
    void update(double currTime, double rate);
    ~Hash();
    bool completedAllActions();
    bool completeAnimation();
    bool reachedEnd();
    bool reachedStart();
    void ClearOperator();
    inline bool endLoop() { return loop == core.size(); }
    inline bool startLoop() { return loop == 0; }
    void setNULLPos() {
        for (int i = 0; i < m; i++) {
            root[i]->setPosition((Vector2){800, 100});
        }
    }
    std::vector<int> getValues() {
        std::vector<int> values;
        for (int i = 0; i < m; i++) values.push_back(root[i]->value);
        return values;
    }
    void setValues(std::vector<int> values) {
        for (int i = 0; i < m; i++) root[i]->value = values[i];
    }

   private:
    void draw(hashNode *root);
    void DrawArrowWithCircles(Vector2 start, Vector2 end, float radius,
                              Color color, float thickness);
    ItrAction Itr;
    int loop;
    ActionList core;
    std::vector<std::pair<hashNode *, int>> ItrHistory;
    std::vector<int> changeList;
    std::pair<bool, bool> doFadeEffect(double currTime, double TransTime,
                                       hashNode *targetedNode);
    std::pair<ChangeProcedure, hashNode *> changing;

    static const std::vector<std::string> hashInsert;
    static const std::vector<std::string> hashSearch;
    static const std::vector<std::string> hashDelete;
    static const std::vector<std::string> hashUp;
    static void adjustHighlight(int index);
};

#endif  // hash_HPP