#ifndef AVL_HPP
#define AVL_HPP

#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "AVLNode.hpp"
#include "colorPalette.h"
#include "raylib.h"
#include <mLib/changeProcedure.hpp>

class AVL {
   private:
    enum AVLAction {
        INIT,
        CLEAR,
        SETLECT,
        CREATE,
        DELETE,
        RR,
        LL,
        Right,
        Left,
        target,
        untarget,
        changeValue,
        FadeEffect,
    };

    struct ItrAction {
        Animation *animation;
        bool show;
        AVLNode *targetedNode, *preNode;
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
        AVLAction action;
        AVLNode *node;
    };

    typedef std::vector<action> ActionList;

   private:
    float xOFFSET = 100, yOFFSET = 130, NODE_RADIUS = 30;
    AVLNode *root;
    int flag, flagUndo;

   public:
    AVL();
    bool Action(bool isReversed);
    bool doAction(action Action);
    bool Undo(action Action);
    void insert(int value);
    void search(int value);
    void remove(int value);
    void draw();
    void update(double currTime, double rate);
    ~AVL();
    bool completedAllActions();
    bool completeAnimation();
    bool reachedEnd();
    bool reachedStart();
    void ClearOperator();
    inline bool endLoop() { return loop == core.size(); }
    inline bool startLoop() { return loop == 0; }
    inline AVLNode *getRoot() { return root; }
    static ColorSet const *PALETTE;
    void setNULLPos(AVLNode *root);
    void printDebug(AVLNode *root);
   private:
    void calcPosition(AVLNode *root);
    std::vector<AVLNode *> getNodes(AVLNode *root);
    std::pair<int, int> insert(AVLNode *par, AVLNode *&root, int value,
                               std::vector<action> &actions);
    int getLeftmost(AVLNode *root);
    void search(AVLNode *root, int value, std::vector<action> &actions);
    std::pair<int, int> remove(AVLNode *par, AVLNode *root, int value,
                               std::vector<action> &actions);
    void draw(AVLNode *root);
    void drawArrow(AVLNode *root);
    void update(AVLNode *root, double currTime, double rate);
    bool isCompleted(AVLNode *root);
    void DrawArrowWithCircles(Vector2 start, Vector2 end, float radius,
                              Color color, float thickness);
    ItrAction Itr;
    int loop;
    ActionList core;
    std::vector<std::pair<AVLNode *, int>> ItrHistory;
    std::vector<int> changeList, rotateList;
    std::pair<bool, bool> doFadeEffect(AVLNode *root, double currTime,
                                       double TransTime, AVLNode *targetedNode);
    std::pair<ChangeProcedure, AVLNode*>  changing;

};

#endif  // AVL_HPP