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
    TRIE,
    LINKED_LIST,
};

State state = MENU;
TrieState trieState;

using namespace ColorPalette::FlatUI;
using namespace ColorPalette;
int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    TextUtility::init();
    SinglyLinkedList ll(50, GetRenderHeight() / 2, ColorSet{WET_ASPHALT, MIDNIGHT_BLUE, CONCRETE, ASBESTOS, true, GREEN_SEA});

    Button button1(400, 400, 200, 80, "Add Node", 20, ColorSet{WET_ASPHALT, MIDNIGHT_BLUE, CONCRETE, ASBESTOS, false, GREEN_SEA});
    Button button2(600, 400, 200, 80, "Remove End");
    Button testArrow(0, 600, 20, 200, ">", 20, ColorSet{PETER_RIVER, PETER_RIVER, CLOUDS, SILVER, true, WET_ASPHALT});
    int nodeData = 0;
    trieState = TrieState();

    // Button trieButton{10, 10, 100, 50, "Trie", 20, MIDNIGHT_BLUE, SILVER, ASBESTOS};
    Button backButton{10, 10, 100, 50, "Back", 20, {MIDNIGHT_BLUE, MIDNIGHT_BLUE, CLOUDS, CONCRETE, true, WET_ASPHALT}};
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);  
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x20B2AAFF);    //light sea green
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);    //white
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    // trieState.
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
                if (WelcomeMenu::isLinkedListPressed()) {state = LINKED_LIST;}
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
            case LINKED_LIST: {
                backButton.render();
                if (backButton.isPressed()) {
                    state = MENU;
                    break;
                }
                ll.render();
                button1.render();
                button2.render();
                testArrow.render();
                if (button1.isPressed()) {
                    nodeData++;
                    ll.addNode(nodeData);
                }
                if (button2.isPressed()) {
                    nodeData--;
                    if(nodeData<= 0) nodeData = 1;
                    ll.removeEnd();

                }
                break;
            }
        }
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}