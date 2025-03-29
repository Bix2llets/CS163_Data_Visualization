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

// Main function
int main() {
    // Initialize Raylib and Raygui
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    SetTextureFilter(DrawUtility::inter20.texture, TEXTURE_FILTER_TRILINEAR);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    // Configure Raygui goes here
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

    // Intialize components
    srand(time(NULL));
    DrawUtility::init();
    AppMenu::init();
    SLLScene::setSpecs(0.05f);
    SLLScene::init();
    Animation::setUpdateRate(5.f);
    AnimationColor::setUpdateRate(1.f);

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

    // MenuPane pane({100, 100}, &GBLight::BACKGROUND1, &BUTTON_SET_1, &BUTTON_SET_1);
    // pane.newLine(0, 2, "Testing", {"TEST1", "TEST2"});
    // pane.newLine(1, 2, "Testing", {"TEST1", "TEST2"});
    // pane.newLine(2, 2, "Testing", {"TEST1", "TEST2"});
    // Main application loop
    while (!WindowShouldClose()) {
        // Update goes here
        Loop::registerInput();
        Loop::update();
        // Render goes here
        BeginDrawing();
        ClearBackground(backgroundColor);
        Loop::render();
        EndDrawing();
    }

    // On exit events
    std::cout << "Program ran successfully\n";
    CloseWindow();
}