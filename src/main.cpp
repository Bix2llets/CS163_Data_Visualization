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
    TextUtility::init();
    SinglyLinkedList ll(50, GetRenderHeight() / 2, elementTheme);

    Button button1(400, 400, 200, 80, "Add Node", 20, elementTheme);
    Button button2(600, 400, 200, 80, "Remove End", 20, elementTheme);
    Button testArrow(0, 600, 20, 200, ">", 20, elementTheme);
    int nodeData = 0;
    trieState = TrieState();

    // Button trieButton{10, 10, 100, 50, "Trie", 20, MIDNIGHT_BLUE, SILVER,
    // ASBESTOS};
    Button backButton{10, 10, 100, 50, "Back", 20, elementTheme};
    TextBox textBox1{{300, 0, 300, 50}, elementTheme};
    TextBox textBox2{{300, 100, 300, 50}, elementTheme};
    TextBox textBox3{{300, 200, 300, 50}, elementTheme};
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x20B2AAFF);  // light sea green
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);  // white
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    Animation aniTest{50, 50, 9};
    Button aniButtonLeft(100, 100, 50, 50, "Left");
    Button aniButtonRight(200, 100, 50, 50, "Right");
    Button aniButtonUp(150, 50, 50, 50, "Up");
    Button aniButtonDown(150, 100, 50, 50, "Down");
    // trieState.
    while (!WindowShouldClose()) {
        accumulatedTime += GetFrameTime();
        while (accumulatedTime > DELTA_TIME) {
            accumulatedTime -= DELTA_TIME;
            frameCount++;
        }
        while (frameCount) {
            aniTest.update();
            frameCount--;
        }
        if (aniButtonLeft.isPressed())
            aniTest.setTargetedPosition(
                Vector2Add(aniTest.getPosition(), {-50, 0}));
        if (aniButtonRight.isPressed())
            aniTest.setTargetedPosition(
                Vector2Add(aniTest.getPosition(), {+50, 0}));
        if (aniButtonUp.isPressed())
            aniTest.setTargetedPosition(
                Vector2Add(aniTest.getPosition(), {0, -50}));
        if (aniButtonDown.isPressed())
            aniTest.setTargetedPosition(
                Vector2Add(aniTest.getPosition(), {0, 50}));
        BeginDrawing();
        ClearBackground(RAYWHITE);
        aniTest.render();
        aniButtonLeft.render();
        aniButtonRight.render();
        aniButtonUp.render();
        aniButtonDown.render();

        // switch ( state )
        // {
        //     case MENU:
        //     {
        //         WelcomeMenu::render();
        //         if (WelcomeMenu::isTriePressed()) {
        //             state = TRIE;
        //         }
        //         if (WelcomeMenu::isLinkedListPressed()) {state =
        //         LINKED_LIST;} break;
        //     }
        //     case TRIE:
        //     {
        //         backButton.render();
        //         trieState.handleInput();
        //         trieState.update();
        //         trieState.render();
        //         if (backButton.isPressed()) {
        //             state = MENU;
        //         }
        //         break;
        //     }
        //     case LINKED_LIST: {
        //         textBox1.render();
        //         textBox2.render();
        //         textBox3.render();
        //         backButton.render();
        //         if (backButton.isPressed()) {
        //             state = MENU;
        //             break;
        //         }
        //         ll.render();
        //         button1.render();
        //         button2.render();
        //         testArrow.render();
        //         if (button1.isPressed()) {
        //             nodeData++;
        //             ll.addNode(nodeData);
        //         }
        //         if (button2.isPressed()) {
        //             nodeData--;
        //             if(nodeData<= 0) nodeData = 1;
        //             ll.removeEnd();

        //         }
        //         break;
        //     }
        // }
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}