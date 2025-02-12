#include "raylib.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;
const int NODE_RADIUS = 20;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 40;


struct TrieNode {
    Vector2 position;
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
    private:
        float xOFFSET = 100, yOFFSET = 50;
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
                }
                current = current->children[c];
            }
            current->isEndOfWord = true;
        }
        
        Vector2 calcPosition(TrieNode *root) {
            Vector2 width = {0, 0};
            std::vector<Vector2> widthList;
            std::vector<TrieNode*> queue;
            for (auto &child : root->children) {
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
        void draw(TrieNode *root, int x, int y) {
            if (root == NULL) {
                return;
            }
            DrawCircle(x, y, NODE_RADIUS, root->isEndOfWord ? RED : BLACK);
            for (auto &child : root->children) {
                DrawLine(x, y, child.second->position.x + x, child.second->position.y + y, BLACK);
                draw(child.second, child.second->position.x + x, child.second->position.y + y);
            }
        }
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Trie Visualization");
    SetTargetFPS(60);
    Trie trie;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("hellocode");
    trie.insert("worldcode");
    trie.insert("worlds");
    trie.calcPosition(trie.root);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        trie.draw(trie.root, SCREEN_WIDTH / 2, 50);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
