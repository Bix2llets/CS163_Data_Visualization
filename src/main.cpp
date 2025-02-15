#include "raylib.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include "..\..\..\src\Trie.hpp"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Trie Visualization");
    SetTargetFPS(60);
    Trie trie;
    trie.root->valid = true;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("hellocode");
    trie.insert("worldcode");
    trie.insert("worlds");
    trie.calcPosition(trie.root);
    trie.calcPosition2(trie.root);
    std::cout << trie.move(trie.root) << std::endl;
    std::queue<TrieNode*> result = trie.insertAnimation("worldhello");
    float lastUpdate = 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        trie.drawLine(trie.root, SCREEN_WIDTH / 2, 50);
        trie.draw(trie.root, SCREEN_WIDTH / 2, 50);
        lastUpdate += 0.05;
        trie.move(trie.root);
        if (lastUpdate > 1)
        {
            lastUpdate = 0;
            if (!result.empty()) {
                if (trie.move(trie.root)) continue;
                if (result.front()->valid == 0)
                {
                    result.front()->valid = 1;
                    trie.calcPosition2(trie.root);
                }
                result.front()->selected = 1;
                result.pop();
            }
        }
        EndDrawing();
    }

     CloseWindow();
    return 0;
}
