// Include necessary libraries and headers
#define RAYGUI_IMPLEMENTATION
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <mLib/Utility.hpp>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "AVLState.hpp"
#include "GraphScene.h"
#include "MenuPane.h"
#include "TrieState.hpp"
#include "appMenu.h"
#include "colorPalette.h"
#include "form.h"
#include "hashState.hpp"
#include "mainLoop.h"
#include "raygui.h"
#include "singlyLInkedList.h"
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

ColorSet elementTheme = {WET_ASPHALT,
                         MIDNIGHT_BLUE,
                         CLOUDS,
                         ASBESTOS,
                         DrawUtility::EDGE_NORMAL,
                         DrawUtility::EDGE_HIGHLIGHTED};

Color backgroundColor = GBLight::BACKGROUND4;

void raylibInit() {
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);
    DrawUtility::init();
    GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL,
                ColorToInt(AppMenu::buttonPalette->borderNormal));
    GuiSetStyle(SLIDER, BORDER_COLOR_FOCUSED,
                ColorToInt(AppMenu::buttonPalette->borderNormal));
    GuiSetStyle(SLIDER, BORDER_COLOR_PRESSED,
                ColorToInt(AppMenu::buttonPalette->borderNormal));
    GuiSetStyle(SLIDER, BORDER_WIDTH, 2);
    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL,
                ColorToInt(AppMenu::buttonPalette->backgroundNormal));
    GuiSetStyle(SLIDER, BASE_COLOR_FOCUSED,
                ColorToInt(AppMenu::buttonPalette->backgroundHighlight));
    GuiSetStyle(SLIDER, BASE_COLOR_PRESSED,
                ColorToInt(GBLight::FOREGROUND4));
    GuiSetStyle(SLIDER, TEXT_COLOR_NORMAL,
                ColorToInt(AppMenu::buttonPalette->textNormal));
    GuiSetStyle(SLIDER, TEXT_COLOR_FOCUSED,
                ColorToInt(AppMenu::buttonPalette->textHighlight));
    GuiSetStyle(SLIDER, TEXT_COLOR_PRESSED,
                ColorToInt(AppMenu::buttonPalette->textHighlight));
    GuiSetStyle(DEFAULT, TEXT_SIZE, DrawUtility::NORMAL_SIZE);
    GuiSetFont(DrawUtility::inter20);
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
    AppMenu::init();
    SLLScene::init();
    GraphScene::init();
    mLib::Init();
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
    AppMenu::loadCode(exampleCode);
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
    SLLScene::clearScene();
}