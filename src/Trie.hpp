#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include "raylib.h"
#include "..\..\..\src\TrieNode.hpp"

class Trie {
    private:
        float xOFFSET = 100, yOFFSET = 55, NODE_RADIUS = 20;
        Vector2 Lerp(Vector2 start, Vector2 end, float t) {
            Vector2 direction = {end.x - start.x, end.y - start.y};
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 1.0)
            {
                direction.x /= length;
                direction.y /= length;
                return {start.x + direction.x * t, start.y + direction.y * t};
            }
            return end;
        }        
    public: 
        TrieNode* root;
        Trie() {
                root = new TrieNode();
        }

        void insert(std::string word) {
            TrieNode* current = root;
            for (char c : word) {
                if (current->children.find(c) == current->children.end()) {
                    current->children[c] = new TrieNode();
                    current->children[c]->valid = true;
                }
                current = current->children[c];
            }
            current->isEndOfWord = true;
        }
        
        Vector2 calcPosition(TrieNode *root) {
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
                queue[mid1]->position = (Vector2){- (widthList[mid1].y + xOFFSET / 2), yOFFSET};
                queue[mid2]->position = (Vector2){widthList[mid2].x + xOFFSET / 2, yOFFSET};
                width.x = widthList[mid1].x + widthList[mid1].y + xOFFSET / 2;
                width.y = widthList[mid2].x + widthList[mid2].y + xOFFSET / 2;

            } else {
                mid1 = queue.size() / 2;
                mid2 = queue.size() / 2;

                queue[mid1]->position = (Vector2){0, yOFFSET};
                width = widthList[mid1];
            }
            for (int i = 0; i < mid1; i++) {
                queue[i]->position = (Vector2){- (width.x + widthList[i].y + xOFFSET / 2), yOFFSET};
                width.x += widthList[i].x + widthList[i].y + xOFFSET / 2;
            }
            for (int i = mid2 + 1; i < queue.size(); i++) {
                queue[i]->position = (Vector2){width.x + widthList[i].y + xOFFSET / 2, yOFFSET};
                width.y += widthList[i].x + widthList[i].y + xOFFSET / 2;
            }

            return width;
        }
        Vector2 calcPosition2(TrieNode *root) {
            Vector2 width = {0, 0};
            std::vector<Vector2> widthList;
            std::vector<TrieNode*> queue;
            for (auto &child : root->children) 
                if (child.second->valid) {
                queue.push_back(child.second);
                widthList.push_back(calcPosition2(child.second));
            }
            if (queue.size() == 0) return width;
            int mid1, mid2;
            if (queue.size() % 2 == 0) {
                mid1 = queue.size() / 2 - 1;
                mid2 = queue.size() / 2;
                queue[mid1]->currentPosition = (Vector2){- (widthList[mid1].y + xOFFSET / 2), yOFFSET};
                queue[mid2]->currentPosition = (Vector2){widthList[mid2].x + xOFFSET / 2, yOFFSET};
                width.x = widthList[mid1].x + widthList[mid1].y + xOFFSET / 2;
                width.y = widthList[mid2].x + widthList[mid2].y + xOFFSET / 2;
            } else {
                mid1 = queue.size() / 2;
                mid2 = queue.size() / 2;

                queue[mid1]->currentPosition = (Vector2){0, yOFFSET};
                width = widthList[mid1];
            }
            for (int i = 0; i < mid1; i++) {
                queue[i]->currentPosition = (Vector2){- (width.x + widthList[i].y + xOFFSET / 2), yOFFSET};
                width.x += widthList[i].x + widthList[i].y + xOFFSET / 2;
            }
            for (int i = mid2 + 1; i < queue.size(); i++) {
                queue[i]->currentPosition = (Vector2){width.x + widthList[i].y + xOFFSET / 2, yOFFSET};
                width.y += widthList[i].x + widthList[i].y + xOFFSET / 2;
            }
            return width;
        }

        void drawLine(TrieNode*root, int x, int y) {
            if (root == NULL) {
                return;
            }
            for (auto &child : root->children) 
                if (child.second->valid) {
                DrawLineEx((Vector2){x, y}, (Vector2){child.second->position.x + x, child.second->position.y + y}, 3, BLACK);
                drawLine(child.second, child.second->position.x + x, child.second->position.y + y);
            }
        }
        void draw(TrieNode *root, int x, int y) {
            //std::cout << "Drawing" << std::endl;
            if (root == NULL) {
                return;
            }
            DrawCircle(x, y, NODE_RADIUS, root->selected ? GREEN : root->isEndOfWord ? RED : BLACK);
            for (auto &child : root->children) 
                if (child.second->valid) {
                draw(child.second, child.second->position.x + x, child.second->position.y + y);
            }
        }
        std::queue<TrieNode*> search(std::string word) {
            std::queue<TrieNode*> result;
            result.push(root);
            TrieNode* current = root;
            for (char c : word) {
                if (current->children.find(c) == current->children.end()) {
                    return result;
                }
                current = current->children[c];
                result.push(current);
            }
            return result;
        }
        std::queue<TrieNode*> insertAnimation(std::string word) {
            std::queue<TrieNode*> result;
            result.push(root);
            TrieNode* current = root;
            for (char c : word) {
                if (current->children.find(c) == current->children.end()) {
                    current->children[c] = new TrieNode();
                }
                current = current->children[c];
                result.push(current);
            }
            return result;
        }
        bool move(TrieNode *root)
        {
            bool moved = false;
            if (root == NULL) return false;
            for (auto &child : root->children) {
                if (child.second->currentPosition.x != child.second->position .x || child.second->currentPosition.y != child.second->position.y) {
                    moved = true;
                    child.second->position = Lerp(child.second->position, child.second->currentPosition, 5);
                }
                if (move(child.second)) moved = true;
            }
            return moved;
        }
};


#endif // TRIE_HPP