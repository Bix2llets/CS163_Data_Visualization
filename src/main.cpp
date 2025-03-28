#define RAYGUI_IMPLEMENTATION
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "GraphScene.h"
#include "SLLScene.h"
#include "TrieState.hpp"
#include "animation.h"
#include "appMenu.h"
#include "arrow.h"
#include "button.h"
#include "colorPalette.h"
#include "form.h"
#include "mainLoop.h"
#include "raygui.h"
#include "raylib.h"
#include "singlyLInkedList.h"
#include "utility.h"
#include "welcomeMenu.h"
#include "mLib/Utility.hpp"
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
    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt(Color{229, 189, 80, 255}));
    GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, ColorToInt(Color{229, 189, 80, 255}));
    GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, ColorToInt(Color{229, 189, 80, 255}));
    GuiSetStyle(DEFAULT, BORDER_WIDTH, 2);
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt(Color{51, 49, 45, 255}));  
    GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, ColorToInt(Color{42, 114, 47, 255}));
    GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, ColorToInt(Color{51, 49, 45, 255}));
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(Color{42, 114, 47, 255}));
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(Color{186, 180, 163, 255}));  
    GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, ColorToInt(Color{186, 180, 163, 255}));  
    GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(Color{186, 180, 163, 255}));
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    mLib::Init();
    GuiSetFont(mLib::mFont);
    // * Raylib/Raygui initialization
    srand(time(NULL));
    DrawUtility::init();
    AppMenu::init();
    SLLScene::setSpecs(0.05f);
    SLLScene::init();

    Animation::setUpdateRate(10.f);
    AnimationColor::setUpdateRate(1.f);
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

    GraphScene::addEdge(1, 2, rand());
    GraphScene::addEdge(2, 3, rand());
    GraphScene::addEdge(3, 4, rand());
    GraphScene::addEdge(5, 4, rand());
    GraphScene::addEdge(5, 6, rand());
    GraphScene::addEdge(1, 6, rand());
    GraphScene::addEdge(1, 4, rand());
    GraphScene::addEdge(3, 7, rand());
    GraphScene::addEdge(4, 8, rand());
    GraphScene::addEdge(7, 8, rand());
    GraphScene::addEdge(2, 8, rand());
    GraphScene::addEdge(7, 6, rand());
    GraphScene::addEdge(7, 2, rand());

    // GraphScene::addStep();
    // for (int i = 0; i <= 10; i++)
    // for (int j = 0; j <= 20; j++)
    // GraphScene::addEdgeAdd(i, j, rand());

    // for (int i = 1; i <= 20; i++)
    //     GraphScene::addEdgeAdd(0, i, i);
    while (!WindowShouldClose()) {
        Loop::registerInput();
        Loop::update();
        // GraphScene::update();
        BeginDrawing();
        ClearBackground(backgroundColor);
        Loop::render();
        // GraphScene::render();
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    CloseWindow();
}