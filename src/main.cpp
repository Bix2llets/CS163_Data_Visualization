#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include "TrieState.hpp"
#include "AVLState.hpp"
#include "hashState.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <mLib/Utility.hpp>

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

enum State {
    MENU,
    TRIE,
    AVL,
    HASH_TABLE,
};

State state = MENU;

TrieState trieState;
AVLState avlState;
hashState _hashState;

#include <memory>

#include "GUIObject.h"
#include "button.h"
#include "singlyLInkedList.h"
#include "raylib.h"
#include "utility.h"
#include "colorPalette.h"

using namespace ColorPalette::FlatUI;
int main() {
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);

    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);  
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x20B2AAFF);    //light sea green
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);    //white
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

    Font font = LoadFont("assets/inter-black.ttf");
    GuiSetFont(font);
    mLib::InitFont("assets/inter-black.ttf");
    trieState = TrieState();
    avlState = AVLState();
    _hashState = hashState();
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
                if (GuiButton((Rectangle){10, 70, 100, 50}, "AVL")) {
                    state = AVL;
                }
                if (GuiButton((Rectangle){10, 130, 100, 50}, "Hash")) {
                    state = HASH_TABLE;
                }
                break;
            }
            case TRIE:
            {
                trieState.run();
                if (GuiButton((Rectangle){10, 10, 100, 50}, "Back")) {
                    state = MENU;
                }
                break;
            }
            case AVL:
            {
                avlState.run();
                if (GuiButton((Rectangle){10, 10, 100, 50}, "Back")) {
                    state = MENU;
                }
                break;
            }
            case HASH_TABLE:
            {
                _hashState.printTable();
                _hashState.run();
                if (GuiButton((Rectangle){10, 10, 100, 50}, "Back")) {
                    state = MENU;
                }
                break;
            }
        }
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    UnloadFont(font);
    CloseWindow();
}