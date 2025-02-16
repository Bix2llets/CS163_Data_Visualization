#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include "TrieState.hpp"
#include <memory>

#include "GUIObject.h"
#include "button.h"
#include "singlyLInkedList.h"
#include "raylib.h"
#include "utility.h"
#include "colorPalette.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "welcomeMenu.h"
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

enum State {
    MENU,
    TRIE
};

enum class Scene {
    NONE, 
    AVLTREE, 
    GRAPH,
    TRIE,
    LINKED_LIST,
    HASH,
};
State state = MENU;
Scene currentScene = Scene::NONE;
TrieState trieState;

using namespace ColorPalette::FlatUI;
int main() {
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    TextUtility::init();
    SinglyLinkedList ll(50, GetRenderHeight() / 2);

    ll.setColor(ColorPalette::FlatUI::MIDNIGHT_BLUE, ColorPalette::FlatUI::FLAT_ORANGE, ColorPalette::FlatUI::WET_ASPHALT);
    // Button button1(400, 400, 100, 50, "Add Node", 12, ASBESTOS, CLOUDS, MIDNIGHT_BLUE);
    // Button button2(500, 400, 100, 50, "Remove End");
    int nodeData = 0;
    trieState = TrieState();

    // Button trieButton{10, 10, 100, 50, "Trie", 20, MIDNIGHT_BLUE, SILVER, ASBESTOS};
    Button backButton{10, 10, 100, 50, "Back", 20, MIDNIGHT_BLUE, SILVER, ASBESTOS};
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
                WelcomeMenu::render();
                if (WelcomeMenu::isTriePressed()) {
                    state = TRIE;
                }
                break;
            }
            case TRIE:
            {
                backButton.render();
                trieState.handleInput();
                trieState.update();
                trieState.render();
                if (backButton.isPressed()) {
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