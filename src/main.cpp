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
#include "mainLoop.h"
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

Color backgroundColor = Color{51, 49, 45, 255};
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
    SLLScene::setSpecs(0.05f);
    SLLScene::init();

    Animation::setUpdateRate(12.5f);
    AnimationColor::setUpdateRate(12.5f);
    // * Object initialization

    std::vector<std::string> exampleCode = {
        "#include <iostream>"
        "",
        "using namespace std",
        "",
        "int main()",
        "{",
        "}"};
    AppMenu::loadCode(exampleCode);



    while (!WindowShouldClose()) {
        Loop::registerInput();
        Loop::update();
        BeginDrawing();
        ClearBackground(backgroundColor);
        Loop::render();
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}