#include "raylib.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <ctime>
#include "..\..\..\src\Trie.hpp"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_RICONS
#include "raygui.h"
#include "..\..\..\src\TrieState.hpp"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

enum class State {
    MainMenu,
    Trie
};

State current_state = State::MainMenu;
TrieState trieState;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Data Visualization");
    SetTargetFPS(60);
    srand(time(0));

    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);  
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x20B2AAFF);    // light sea green
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);    // white 
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (current_state) {
            case State::MainMenu:
                if (GuiButton((Rectangle){10, 10, 100, 40}, "Trie")) {
                    current_state = State::Trie;
                }
                break;
            case State::Trie:
                trieState.handleInput();
                trieState.update();
                trieState.render();
                if (GuiButton((Rectangle){10, 10, 100, 40}, "Back")) {
                    current_state = State::MainMenu;
                }
                break;
        }
        EndDrawing();
    }

     CloseWindow();
    return 0;
}
