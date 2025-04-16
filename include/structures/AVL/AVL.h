#ifndef AVL_HPP
#define AVL_HPP

#include <cmath>
#include <iostream>
#include <mLib/changeProcedure.h>
#include <queue>
#include <string>
#include <vector>

#include "AVLNode.h"
#include "colorPalette.h"
#include "raylib.h"

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

    static const std::vector<std::string> AVLInsert;
    static const std::vector<std::string> AVLSearch;
    static const std::vector<std::string> AVLDelete;
    static const std::vector<std::string> AVLDelete2;
    static const std::vector<std::string> AVLUpdate;

   public:
   void upOldNew(int oldValue, int newValue) {
        ActionList actions;
        actions.push_back({26, INIT, NULL});
        AVLNode *current = root;
        while (current != NULL) {
            if (oldValue < current->value) current = current->left;
            else if (oldValue > current->value) current = current->right;
            else break;
        }
        actions.push_back({26, SETLECT, current});
        std::vector<AVLNode *> nodes;
        if (current != NULL) {
            int lower = -1e9, upper = 1e9;
            AVLNode *temp = current->left;
            while (temp != NULL) {
                lower = std::max(lower, temp->value);
                if (temp->right == NULL) nodes.push_back(temp);
                temp = temp->right;
            }
            temp = current->right;
            while (temp != NULL) {
                upper = std::min(upper, temp->value);
                if (temp->left == NULL) nodes.push_back(temp);
                temp = temp->left;
            }
            temp = current;
            while (temp -> parent) {
                if (temp->PosInParent == 1) {
                    lower = std::max(lower, temp->parent->value);
                    nodes.push_back(temp->parent);
                    break ;
                }
                temp = temp->parent;
            }
            temp = current;
            while (temp -> parent) {
                if (temp->PosInParent == 0) {
                    upper = std::min(upper, temp->parent->value);
                    nodes.push_back(temp->parent);
                    break ;
                }
                temp = temp->parent;
            }
            for (AVLNode *node : nodes) actions.push_back({27, target, node});
            if (lower < newValue && newValue < upper) {
                current->targetValue = newValue;
                actions.push_back({28, changeValue, current});
            }
            for (AVLNode *node : nodes) actions.push_back({29, untarget, node});
            
        }
        actions.push_back({29, SETLECT, NULL});
        actions.push_back({29, CLEAR, NULL});
        core.insert(core.end(), actions.begin(), actions.end());
   }
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
    
    static int highlightingRow;
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
    std::pair<ChangeProcedure, AVLNode *> changing;

    static void adjustHighlight(int index);

};

#endif  // AVL_HPP