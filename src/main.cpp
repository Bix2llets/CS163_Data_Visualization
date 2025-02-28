#define RAYGUI_IMPLEMENTATION
#include <cmath>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "SLLScene.h"
#include "TrieState.hpp"
#include "animation.h"
#include "arrow.h"
#include "button.h"
#include "colorPalette.h"
#include "raygui.h"
#include "raylib.h"
#include "singlyLInkedList.h"
#include "textBox.h"
#include "utility.h"
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
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x20B2AAFF);  // light sea green
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);  // white
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

    // * Raylib/Raygui initialization

    ColorSet elementTheme = {WET_ASPHALT,
                             MIDNIGHT_BLUE,
                             CLOUDS,
                             ASBESTOS,
                             DrawUtility::EDGE_NORMAL,
                             DrawUtility::EDGE_HIGHLIGHTED};
    DrawUtility::init();
    int nodeData = 0;
    Node node1(23, 50, 50, 30);
    Node node2(230, 150, 50, 30);
    Node node3(2300, 250, 50, 30);

    Button addButton{{0, 0, 200, 75}, "Add node at end", 20, elementTheme};
    Button add1Button{{0, 75, 200, 75}, "Add node at 1", 20, elementTheme};
    Button add17Button{{0, 150, 200, 75}, "Add node at 17", 20, elementTheme};
    Button erase1Button{
        {0, 225, 200, 75}, "Remove node at 1", 20, elementTheme};
    Button erase17Button{
        {0, 300, 200, 75}, "Remove node at 17", 20, elementTheme};
    Button eraseButton{
        {0, 375, 200, 75}, "Remove node at 17", 20, elementTheme};
    // * Object initialization
    SLL sll({100, 100, 1400, 400}, 10.0f);
    // trieState.
    while (!WindowShouldClose()) {
        accumulatedTime += GetFrameTime();
        while (accumulatedTime > DELTA_TIME) {
            accumulatedTime -= DELTA_TIME;
            sll.update();
        }
        BeginDrawing();
        ClearBackground(CONCRETE);
        addButton.render();
        add1Button.render();
        add17Button.render();
        eraseButton.render();
        erase17Button.render();
        erase1Button.render();
        sll.render();
        DrawUtility::drawText(std::to_string(GetFPS()), {50, 50},
                              DrawUtility::inter20, BLACK, 20,
                              DrawUtility::SPACING, VerticalAlignment::TOP,
                              HorizontalAlignment::LEFT);
        EndDrawing();

        if (addButton.isPressed()) {
            sll.addEnd(std::to_string(1));
        }
        if (add1Button.isPressed()) {
            sll.addAt(std::to_string(1), 1);
        }
        if (add17Button.isPressed()) {
            for (int i = 0; i < 100; i++) sll.addAt(std::to_string(1), 17);
        }
        if (eraseButton.isPressed()) {
            sll.removeEnd();
        }
        if (erase1Button.isPressed()) {
            sll.removeAt(1);
        }
        if (erase17Button.isPressed()) {
            for (int i = 0; i < 100; i++) sll.removeAt(17);
        }

        
    }

    // for (int i = 0; i < 10; i++) sll.addEnd("1");
    // SLL sll2(sll);
    // Node* root1;
    // Node* root2;
    // root1 = sll.root;
    // root2 = sll2.root;
    // while (root1 && root2) {
    //     std::cout << root1 << " " << root2 << " " << (root1 == root2) <<
    //     "\n"; root1 = root1->nextNode; root2 = root2->nextNode;
    // };
    std::cout << "Program ran successfully\n";
    CloseWindow();
}