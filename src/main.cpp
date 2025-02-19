#include <cmath>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "GUIObject.h"
#include "TrieState.hpp"
#include "button.h"
#include "colorPalette.h"
#include "raylib.h"
#include "singlyLInkedList.h"
#include "textBox.h"
#include "utility.h"
#define RAYGUI_IMPLEMENTATION
#include "animation.h"
#include "arrow.h"
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

const float DELTA_TIME = 1.0 / 24;
float accumulatedTime = 0.0f;
int frameCount = 0;
int main() {
    ColorSet elementTheme = {WET_ASPHALT, MIDNIGHT_BLUE, CLOUDS,
                             ASBESTOS,    true,          MIDNIGHT_BLUE};
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    DrawUtility::init();
    SinglyLinkedList ll(50, GetRenderHeight() / 2, elementTheme);

    Button button1(400, 200, 200, 80, "Add Node", 20, elementTheme);
    Button button2(600, 200, 200, 80, "Remove End", 20, elementTheme);
    Button button3(800, 200, 200, 80, "Reset Animation", 20, elementTheme);
    Button button4(1000, 200, 200, 80, "Add Node Instant", 20, elementTheme);
    Button testArrow(0, 600, 20, 200, ">", 20, elementTheme);
    int nodeData = 0;
    trieState = TrieState();

    // Button trieButton{10, 10, 100, 50, "Trie", 20, MIDNIGHT_BLUE, SILVER,
    // ASBESTOS};
    Button backButton{10, 10, 100, 50, "Back", 20, elementTheme};
    TextBox textBox1{{300, 0, 500, 50}, elementTheme};
    TextBox textBox2{{300, 100, 500, 50}, elementTheme};
    TextBox textBox3{{300, 200, 500
        , 50}, elementTheme};
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x20B2AAFF);  // light sea green
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);  // white
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    Animation aniTest{50, 50, 9};
    AnimationEdge arrowTest{{50, 50}, {100, 100}, BLACK, GREEN, 2};
    ll.setAnimationRate(10);
    // trieState.
    while (!WindowShouldClose()) {
        accumulatedTime += GetFrameTime();
        while (accumulatedTime > DELTA_TIME) {
            accumulatedTime -= DELTA_TIME;
            std::cerr << "Begin update\n";
            ll.update();
            std::cerr << "Updated done\n";
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // arrowTest.render();
        
        // if (IsKeyPressed(KEY_UP)) {
        //     arrowTest.setAnimationBeginPosition(Vector2Add(arrowTest.getBeginPosition(), {0, -50}));
        // }
        // if (IsKeyPressed(KEY_DOWN)) {
        //     arrowTest.setAnimationBeginPosition(Vector2Add(arrowTest.getBeginPosition(), {0, 50}));
        // }
        // if (IsKeyPressed(KEY_LEFT)) {
        //     arrowTest.setAnimationBeginPosition(Vector2Add(arrowTest.getBeginPosition(), {-50, 0}));
        // }
        // if (IsKeyPressed(KEY_RIGHT)) {
        //     arrowTest.setAnimationBeginPosition(Vector2Add(arrowTest.getBeginPosition(), {50, 0}));
        // }
        // if (IsKeyPressed(KEY_W)) {
        //     arrowTest.setAnimationEndPosition(Vector2Add(arrowTest.getEndPosition(), {0, -50}));
        // }
        // if (IsKeyPressed(KEY_S)) {
        //     arrowTest.setAnimationEndPosition(Vector2Add(arrowTest.getEndPosition(), {0, 50}));
        // }
        // if (IsKeyPressed(KEY_A)) {
        //     arrowTest.setAnimationEndPosition(Vector2Add(arrowTest.getEndPosition(), {-50, 0}));
        // }
        // if (IsKeyPressed(KEY_D)) {
        //     arrowTest.setAnimationEndPosition(Vector2Add(arrowTest.getEndPosition(), {50, 0}));
        // }
        // ll.render();
        switch ( state )
        {
            case MENU:
            {
                WelcomeMenu::render();
                if (WelcomeMenu::isTriePressed()) {
                    state = TRIE;
                }
                if (WelcomeMenu::isLinkedListPressed()) {state =
                LINKED_LIST;} break;
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
                // textBox1.render();
                // textBox2.render();
                // textBox3.render();
                backButton.render();
                if (backButton.isPressed()) {
                    state = MENU;
                    break;
                }
                ll.render();
                button1.render();
                button2.render();
                button3.render();
                button4.render();
                textBox1.render();
                textBox2.render();
                textBox3.render();
                if (button1.isPressed()) {
                    nodeData++;
                    ll.addNode(nodeData, false);
                }
                if (button4.isPressed()) {
                    nodeData++;
                    ll.addNode(nodeData, true);
                }
                if (button2.isPressed()) {
                    nodeData--;
                    if(nodeData<= 0) nodeData = 1;
                    ll.removeEnd();

                }
                if (button3.isPressed()) {
                    ll.resetAnimation();
                }
                break;
            }
        }
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}