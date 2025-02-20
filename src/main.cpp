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
    ColorSet elementTheme = {WET_ASPHALT, MIDNIGHT_BLUE,
                             CLOUDS,      ASBESTOS,
                             DrawUtility::EDGE_NORMAL,        DrawUtility::EDGE_HIGHLIGHTED};
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    DrawUtility::init();
    SinglyLinkedList ll(50, GetRenderHeight() / 2, elementTheme, 1.f);
    bool SLLHighlight = false;
    Button button1(400, 200, 200, 80, "Add Node", 20, elementTheme);
    Button button2(600, 200, 200, 80, "Remove End", 20, elementTheme);
    Button button3(800, 200, 200, 80, "Reset Animation", 20, elementTheme);
    Button button4(400, 280, 200, 80, "Set highlight", 20, elementTheme);
    Button button5(600, 280, 200, 80, "deHighlight", 20, elementTheme);
    Button button6(800, 280, 200, 80, "Add node Instant", 20, elementTheme);
    Button testArrow(0, 600, 20, 200, ">", 20, elementTheme);
    int nodeData = 0;
    trieState = TrieState();

    Button backButton{10, 10, 100, 50, "Back", 20, elementTheme};
    TextBox textBox1{{300, 0, 500, 50}, elementTheme};
    TextBox textBox2{{300, 100, 500, 50}, elementTheme};
    TextBox textBox3{{300, 200, 500, 50}, elementTheme};
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x20B2AAFF);  // light sea green
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);  // white
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    Animation aniTest{50, 50, 9};
    AnimationEdge arrowTest{{50, 50}, {100, 100}, AnimationColor{1}, 2};
    ll.setAnimationRate(10.f);
    // trieState.
    while (!WindowShouldClose()) {
        accumulatedTime += GetFrameTime();
        while (accumulatedTime > DELTA_TIME) {
            accumulatedTime -= DELTA_TIME;
            ll.update();
        }
        BeginDrawing();
        ClearBackground(FLAT_ORANGE);
        switch (state) {
            case MENU: {
                WelcomeMenu::render();
                if (WelcomeMenu::isTriePressed()) {
                    state = TRIE;
                }
                if (WelcomeMenu::isLinkedListPressed()) {
                    state = LINKED_LIST;
                }
                break;
            }
            case TRIE: {
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
                if (button1.isPressed()) {
                    nodeData++;
                    ll.addNode(nodeData, false);
                }
                if (button4.isPressed()) {
                    SLLHighlight = !SLLHighlight;
                    ll.setHighlight(SLLHighlight);
                }
                if (button2.isPressed()) {
                    nodeData--;
                    if (nodeData <= 0) nodeData = 1;
                    ll.removeEnd();
                }
                if (button3.isPressed()) {
                    ll.resetAnimation();
                }
                if (button6.isPressed()) {
                    nodeData++;
                    ll.addNode(nodeData, true);
                }
                if (button5.isPressed()) {
                    ll.deHighlight();
                    SLLHighlight = false;
                }
                ll.render();
                button1.render();
                button2.render();
                button3.render();
                button4.render();
                button5.render();
                button6.render();
                textBox1.render();
                textBox2.render();
                textBox3.render();
                break;
            }
        }
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}