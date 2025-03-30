// Include necessary libraries and headers
#define RAYGUI_IMPLEMENTATION
#include "colorPalette.h"
#include "GraphScene.h"
#include "TrieState.hpp"
#include "AVLState.hpp"
#include "appMenu.h"
#include "hashState.hpp"
#include "form.h"
#include "mainLoop.h"
#include "raygui.h"
#include "singlyLInkedList.h"
#include "utility.h"
#include "welcomeMenu.h"
#include <mLib/Utility.hpp>
#include "MenuPane.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// Constants
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;
const float DELTA_TIME = 1.0 / 24;

// Enums and global variables
enum State {
    MENU,
    TRIE,
    AVL,
    HASH_TABLE,
};

State state = MENU;
TrieState trieState;
AVLState avlState;
hashState _hashState;

// Color settings
using namespace ColorPalette::FlatUI;
using namespace ColorPalette;

ColorSet elementTheme = {
    WET_ASPHALT, MIDNIGHT_BLUE, CLOUDS, ASBESTOS,
    DrawUtility::EDGE_NORMAL, DrawUtility::EDGE_HIGHLIGHTED
};

Color backgroundColor = GBLight::BACKGROUND4;

void raylibInit() {
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    
}

void loadSpecs() {
    MenuTable::Constructor((Vector2){10, 650}, (Vector2){200, 50}, (Vector2){700, 750}, (Vector2){50, 50});
    SLLScene::setPanePosition({MenuTable::showMenu.getPosition().x + MenuTable::showMenu.getDimension().x + 20 + MenuTable::basePane.getDimension().x, MenuTable::showMenu.getPosition().y});
    SLLScene::setDelay(0.05f);
    Animation::setUpdateRate(10.f);
    AnimationColor::setUpdateRate(1.f);
    
}

void otherInit() {
    mLib::Init();
    srand(time(NULL));
    DrawUtility::init();
    AppMenu::init();
    SLLScene::init();

}
// Main function
int main() {
    // Initialize Raylib and Raygui
    raylibInit();
    loadSpecs();
    otherInit();
    

    std::vector<std::string> exampleCode = {
        "#include <iostream>",
        "",
        "using namespace std;",
        "",
        "int main()",
        "{",
        "    return 0;",
        "}"
    };
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

    // Button *object = new Button(MenuTable::optionPosition, MenuTable::optionDimension, "Create", 20, AppMenu::buttonPalette);
    // MenuTable::pack(object, MenuTable::CREATE);
    // object = new Button(MenuTable::optionPosition, MenuTable::optionDimension, "Edge Insert", 20, AppMenu::buttonPalette);
    // MenuTable::pack(object, MenuTable::EdgeInsert);
    // object = new Button(MenuTable::optionPosition, MenuTable::optionDimension, "Num Insert", 20, AppMenu::buttonPalette);
    // MenuTable::pack(object, MenuTable::NumInsert);
    // object = new Button(MenuTable::optionPosition, MenuTable::optionDimension, "Text Insert", 20, AppMenu::buttonPalette);
    // MenuTable::pack(object, MenuTable::TextInsert);
    // object = new Button(MenuTable::optionPosition, MenuTable::optionDimension, "MST", 20, AppMenu::buttonPalette);
    // MenuTable::pack(object, MenuTable::None);
    // GraphScene::addStep();
    // for (int i = 0; i <= 10; i++)
    // for (int j = 0; j <= 20; j++)
    // GraphScene::addEdgeAdd(i, j, rand());

    // for (int i = 1; i <= 20; i++)
    //     GraphScene::addEdgeAdd(0, i, i);
    while (!WindowShouldClose()) {
        // Update goes here
        Loop::registerInput();
        Loop::update();
        // Render goes here
        BeginDrawing();
        ClearBackground(backgroundColor);
        // pane.render();
        Loop::render();
        EndDrawing();
    }

    // On exit events
    std::cout << "Program ran successfully\n";
    CloseWindow();
}