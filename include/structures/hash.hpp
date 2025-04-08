#ifndef hash_HPP
#define hash_HPP

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include "raylib.h"
#include "hashNode.hpp"
#include "colorPalette.h"
#include <mLib/changeProcedure.hpp>
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
                if (targetedNode == NULL) animation->setTargetedPosition((Vector2){0, 0});
                else animation->setTargetedPosition(targetedNode->getTargetedPosition());
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
            hashNode* node;
        };

        typedef std::vector<action> ActionList;
    private:
        float xOFFSET = 100, yOFFSET = 130, NODE_RADIUS = 30;
        int m, flag, flagUndo;
        std::vector<hashNode *> root;
    public: 
        static ColorSet const *PALETTE;
        void printTable();
        Hash(int _m) ;
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
            for (int i = 0; i < m; i++) {
                if (root[i]->value != -1) values.push_back(root[i]->value);
            }
            return values;
        }
    private:
        void draw(hashNode *root);
        void DrawArrowWithCircles(Vector2 start, Vector2 end, float radius, Color color, float thickness);
        ItrAction Itr;
        int loop;
        ActionList core;
        std::vector<std::pair<hashNode*, int>> ItrHistory;
        std::vector<int> changeList;
        std::pair<bool, bool> doFadeEffect(double currTime, double TransTime, hashNode *targetedNode);
        std::pair<ChangeProcedure, hashNode*>  changing;
};


#endif // hash_HPP