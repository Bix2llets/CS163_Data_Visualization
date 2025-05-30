#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include "raylib.h"
#include "TrieNode.h"
#include "colorPalette.h"
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
            TrieNode *targetedNode, *preNode;
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
            TrieAction action;
            TrieNode* node;
        };
        
        typedef std::vector<action> ActionList;
    private:
        float xOFFSET = 100, yOFFSET = 100, NODE_RADIUS = 25;
        TrieNode* root;
        int flag, flagUndo;
    public: 
        static ColorSet const *PALETTE;
        static Color const *finalNodeColor;
        static int highlightingRow; 
        
        Trie() ;
        void updateOldNew(std::string oldWord, int newSize) {
            if (newSize <= 0) return;
            ActionList actions;
            TrieNode *current = root;
            actions.push_back({20, INIT, current});
            actions.push_back({21, SETLECT, current});
            for (int i = 0; i < oldWord.size(); i++) {
                if (current->children.find(oldWord[i]) == current->children.end()) {
                    actions.push_back({23, SETLECT, NULL});
                    actions.push_back({23, CLEAR, current});
                    core.insert(core.end(), actions.begin(), actions.end());
                    return ;
                }
                current = current->children[oldWord[i]];
                actions.push_back({21, SETLECT, current});
            }
            if (!current->isEndOfWord) {
                actions.push_back({23, SETLECT, NULL});
                actions.push_back({23, CLEAR, current});
                core.insert(core.end(), actions.begin(), actions.end());
                return ;
            }
            bool flag = current->isEndOfWord & current->children.size() == 0;
            if (flag == 0) {
                actions.push_back({22, SETLECT, NULL});
                actions.push_back({22, UNSETEND, current});
                while (newSize--) current = current->parent;
                actions.push_back({22, SETEND, current});
                actions.push_back({23, CLEAR, current});
                core.insert(core.end(), actions.begin(), actions.end());
                return ;
            }
            newSize = oldWord.size() - newSize;
            while (flag && current != root && newSize) {
                TrieNode *parent = current->parent;
                actions.push_back({22, SETLECT, parent});
                if (current->isEndOfWord) actions.push_back({22, UNSETEND, current});
                actions.push_back({22, DELETE, current});
                newSize--;
                current = parent;
                if (current->children.size() > 1 || current->isEndOfWord) flag = false;
            }
            actions.push_back({22, SETLECT, NULL});
            while (newSize--) current = current->parent;
            actions.push_back({22, SETEND, current});
            actions.push_back({23, CLEAR, current});
            core.insert(core.end(), actions.begin(), actions.end());
        }
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
        TrieNode *getRoot() { return root; }
        void setNULLPos(TrieNode *root) {
            if (root == NULL) return;
            root->setPosition((Vector2){800, 100});
            for (auto child : root->children) {
                setNULLPos(child.second);
            }
        }
        std::vector<std::string> getWords() {
            std::vector<std::string> words;
            std::queue<std::pair<TrieNode *, std::string> > nodeQueue;
            if (root) nodeQueue.push({root, ""});
            while (!nodeQueue.empty()) {
                auto current = nodeQueue.front();
                nodeQueue.pop();
                TrieNode *node = current.first;
                std::string prefix = current.second;
                if (node->isEndOfWord) {
                    words.push_back(prefix);
                }
                for (auto child : node->children) {
                    nodeQueue.push({child.second, prefix + child.first});
                }
            }
            return words;
        }
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

        static const std::vector<std::string> TrieInsert; 
        static const std::vector<std::string> TrieSearch;
        static const std::vector<std::string> TrieDelete;
        static const std::vector<std::string> TrieDelete2;
        static const std::vector<std::string> TrieUpdate;
        
        static void adjustHighlight(int index); 
    };
    
    
    #endif // TRIE_HPP