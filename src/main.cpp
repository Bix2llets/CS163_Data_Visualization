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
    TextUtility::init();
    SinglyLinkedList ll(50, GetRenderHeight() / 2);

    ll.setColor(ColorPalette::FlatUI::MIDNIGHT_BLUE, ColorPalette::FlatUI::FLAT_ORANGE, ColorPalette::FlatUI::WET_ASPHALT);
    Button button1(400, 400, 100, 50, "Add Node", 12, ASBESTOS, CLOUDS, MIDNIGHT_BLUE);
    Button button2(500, 400, 100, 50, "Remove End");
    int nodeData = 0;
    trieState = TrieState();

    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);  
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x20B2AAFF);    //light sea green
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);    //white
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

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
    std::cout << "Program ran successfully\n";
    CloseWindow();
}