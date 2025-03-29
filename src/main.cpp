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
    mLib::Init();
    srand(time(NULL));
    DrawUtility::init();
    AppMenu::init();
    SLLScene::setSpecs(0.05f);
    SLLScene::init();
    MenuTable::Constructor((Vector2){10, 650}, (Vector2){200, 50}, (Vector2){700, 750}, (Vector2){50, 50});

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

    Button *object = new Button(MenuTable::optionPosition, MenuTable::optionDimension, "Create", 20, AppMenu::buttonPalette);
    MenuTable::pack(object, MenuTable::CREATE);
    object = new Button(MenuTable::optionPosition, MenuTable::optionDimension, "Edge Insert", 20, AppMenu::buttonPalette);
    MenuTable::pack(object, MenuTable::EdgeInsert);
    object = new Button(MenuTable::optionPosition, MenuTable::optionDimension, "Num Insert", 20, AppMenu::buttonPalette);
    MenuTable::pack(object, MenuTable::NumInsert);
    object = new Button(MenuTable::optionPosition, MenuTable::optionDimension, "Text Insert", 20, AppMenu::buttonPalette);
    MenuTable::pack(object, MenuTable::TextInsert);
    object = new Button(MenuTable::optionPosition, MenuTable::optionDimension, "MST", 20, AppMenu::buttonPalette);
    MenuTable::pack(object, MenuTable::None);
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