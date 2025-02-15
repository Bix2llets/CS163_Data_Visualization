#include "raylib.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include "..\..\..\src\TrieState.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

enum State {
    MENU,
    TRIE
};

State state = MENU;

TrieState trieState;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Trie Visualization");
    SetTargetFPS(60);
    trieState = TrieState();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch ( state )
        {
            case MENU:
            {
                if (GuiButton((Rectangle){10, 10, 100, 50}, "Trie")) {
                    state = TRIE;
                }
                break;
            }
            case TRIE:
            {
                trieState.handleInput();
                trieState.update();
                trieState.render();
                if (GuiButton((Rectangle){10, 10, 100, 50}, "Back")) {
                    state = MENU;
                }
                break;
            }
        }
        EndDrawing();
    }

     CloseWindow();
    return 0;
}
