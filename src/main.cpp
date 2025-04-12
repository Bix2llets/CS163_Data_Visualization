// Include necessary libraries and headers
#define RAYGUI_IMPLEMENTATION
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "Utility.h"
#include "AVLScene.h"
#include "GraphScene.h"
#include "MenuPane.h"
#include "TrieScene.h"
#include "codePane.h"
#include "colorPalette.h"
#include "form.h"
#include "hashScene.h"
#include "mainLoop.h"
#include "raygui.h"
#include "SLL/singlyLInkedList.h"
#include "utility.h"
#include "welcomeMenu.h"

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
HashState _hashState;

// Color settings
using namespace ColorPalette::FlatUI;
using namespace ColorPalette;

Color backgroundColor = GBLight::BACKGROUND4;
void raylibInit() {
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    buttonColorSet = BUTTON_SET_LIGHT;
    nodeColorSet = COLOR_SET_LIGHT;
    Utility::init();
    GuiSetStyle(DEFAULT, TEXT_SIZE, Utility::NORMAL_SIZE);
    GuiSetFont(Utility::inter20);
}

void loadSpecs() {
    MenuTable::Constructor((Vector2){10, 650}, (Vector2){200, 50},
                           (Vector2){700, 750}, (Vector2){50, 50});
    
    Vector2 menuPanePosition = {MenuTable::showMenu.getPosition().x +
        MenuTable::showMenu.getDimension().x + 20 +
        MenuTable::basePane.getDimension().x,
    MenuTable::showMenu.getPosition().y};

    SLLScene::setPanePosition(menuPanePosition);
    SLLScene::setDelay(0.05f);

    GraphScene::setPanePosition(menuPanePosition);
    AVLState::initPanes(menuPanePosition);
    TrieState::initPanes(menuPanePosition);
    HashState::initPanes(menuPanePosition); // Already static
    Animation::setUpdateRate(10.f);
    AnimationColor::setUpdateRate(1.f);
}

void otherInit() {
    srand(time(NULL));
    CodePane::init();
    SLLScene::init();
    GraphScene::init();
    Loop::setColorPalette();
    Loop::configSlider();
}
// Main function
int main() {
    // Initialize Raylib and Raygui
    raylibInit();
    loadSpecs();
    otherInit();

    std::vector<std::string> exampleCode = {
        "#include <iostream>", "",  "using namespace std;", "",
        "int main()",          "{", "    return 0;",        "}"};
    CodePane::loadCode(exampleCode);
    while (!WindowShouldClose()) {
        // Update goes here
        Loop::registerInput();
        Loop::update();
        // Render goes here
        BeginDrawing();
        ClearBackground(buttonColorSet.backgroundNormal);
        // pane.render();
        Loop::render();
        EndDrawing();
    }

    // On exit events
    std::cout << "Program ran successfully\n";
    CloseWindow();
    SLLScene::clearScene();
}