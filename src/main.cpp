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
#include "appMenu.h"
#include "arrow.h"
#include "button.h"
#include "colorPalette.h"
#include "form.h"
#include "raygui.h"
#include "raylib.h"
#include "singlyLInkedList.h"
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
ColorSet elementTheme = {WET_ASPHALT,
                         MIDNIGHT_BLUE,
                         CLOUDS,
                         ASBESTOS,
                         DrawUtility::EDGE_NORMAL,
                         DrawUtility::EDGE_HIGHLIGHTED};
int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x20B2AAFF);  // light sea green
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);  // white
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

    // * Raylib/Raygui initialization

    DrawUtility::init();
    AppMenu::init();
    SLLScene::setSpecs(0.0f, 12.5f);
    // * Object initialization
    // trieState.

    std::vector<std::string> exampleCode = {
        "#include <iostream>"
        "",
        "using namespace std",
        "",
        "int main()",
        "{",
        "}"
    };
    AppMenu::loadCode(exampleCode);
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);
        AppMenu::render();
        EndDrawing();
        // accumulatedTime += GetFrameTime();
        // while (accumulatedTime > DELTA_TIME) {
        //     accumulatedTime -= DELTA_TIME;
        //     SLLScene::update();
        // }
        // BeginDrawing();
        // ClearBackground(CONCRETE);
        // addButton.render();
        // add1Button.render();
        // add17Button.render();
        // eraseButton.render();
        // erase17Button.render();
        // erase1Button.render();
        // findButton.render();
        // SLLScene::render();
        // locationBox.render();
        // valueBox.render();
        // DrawUtility::drawText(std::to_string(GetFPS()), {500, 500},
        //                       DrawUtility::inter20, BLACK, 20,
        //                       DrawUtility::SPACING, VerticalAlignment::TOP,
        //                       HorizontalAlignment::LEFT);
        // EndDrawing();
        // auto value = valueBox.getText();
        // auto location = locationBox.getValue();
        // if (addButton.isPressed()) {
        //     SLLScene::addEnd(std::to_string(1));
        // }
        // if (add1Button.isPressed()) {
        //     SLLScene::addAt(std::to_string(1), 1);
        // }
        // if (add17Button.isPressed()) {
        //     if (location.first) SLLScene::addAt(value, location.second);
        // }
        // if (eraseButton.isPressed()) {
        //     SLLScene::removeEnd();
        // }
        // if (erase1Button.isPressed()) {
        //     SLLScene::removeAt(1);
        // }
        // if (erase17Button.isPressed()) {
        //     if (location.first) SLLScene::removeAt(location.second);
        // }
        // if (findButton.isPressed()) {
        //     SLLScene::find(value);
        // }
    }

    // for (int i = 0; i < 10; i++) sll.addEnd("1");
    // SLL sll2 = sll.clone();
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