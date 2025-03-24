#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include "raylib.h"
#include "TrieNode.hpp"

class Trie {
    private:
        enum TrieAction {
            INIT,
            CLEAR,
            SETLECT,
            CREATE,
            DELETE,
            SETEND,
            UNSETEND,
            FadeEffect,
        };
        
        struct ItrAction {
            Animation *animation;
            bool show;
            TrieNode *targetedNode;
            void setTarget() {
                if (targetedNode == NULL) animation->setTargetedPosition((Vector2){0, 0});
                else animation->setTargetedPosition(targetedNode->getTargetedPosition());
            }
            ItrAction() {
                animation = new Animation(0, 0);
                targetedNode = NULL;
                show = false;
            }
        };
        
        struct action {
            int index;
            TrieAction action;
            TrieNode* node;
        };
        
        typedef std::vector<action> ActionList;
    private:
        float xOFFSET = 100, yOFFSET = 130, NODE_RADIUS = 30;
        TrieNode* root;
        int flag, flagUndo;
    public: 
        Trie() ;
        bool Action(bool isReversed);
        bool doAction(action Action);
        bool Undo(action Action);
        void insert(std::string word);
        void search(std::string word);
        void remove(std::string word);
        void draw();
        void update(double currTime, double rate);
        ~Trie();
        bool completedAllActions();
        bool completeAnimation();
        bool reachedEnd();
        bool reachedStart();
        void ClearOperator();
        inline bool endLoop() { return loop == core.size(); }
        inline bool startLoop() { return loop == 0; }
    private:
        Vector2 calcPosition(TrieNode *root);
        void APosition(TrieNode *root);
        void draw(TrieNode *root);
        void drawArrow(TrieNode *root);
        void update(TrieNode *root, double currTime, double rate);
        bool isCompleted(TrieNode *root);
        void DrawArrowWithCircles(Vector2 start, Vector2 end, float radius, Color color, float thickness);
        ItrAction Itr;
        int loop;
        ActionList core;
        std::vector<std::pair<TrieNode*, int>> ItrHistory;
        std::pair<bool, bool> doFadeEffect(TrieNode *root, double currTime, double TransTime, TrieNode *targetedNode);
};


#endif // TRIE_HPP