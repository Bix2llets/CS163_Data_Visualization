#define RAYGUI_IMPLEMENTATION
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "GraphScene.h"
#include <queue>
#include <cmath>
#include "TrieState.hpp"
#include "AVLState.hpp"
#include "appMenu.h"
#include "hashState.hpp"
#define RAYGUI_IMPLEMENTATION
#include "form.h"
#include "mainLoop.h"
#include "raygui.h"
#include <mLib/Utility.hpp>

#include "raylib.h"
#include "singlyLInkedList.h"
#include "utility.h"
#include "welcomeMenu.h"
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

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

#include <memory>

#include "GUIObject.h"
#include "button.h"
#include "singlyLInkedList.h"
#include "raylib.h"
#include "utility.h"
#include "colorPalette.h"

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
    InitWindow(1600, 900, "CS163 Data visualizer");
    SetTargetFPS(60);

    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x008080FF);  
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x20B2AAFF);    //light sea green
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);    //white
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

    Font font = LoadFont("assets/inter-black.ttf");
    GuiSetFont(font);
    mLib::InitFont("assets/inter-black.ttf");
    trieState = TrieState();
    avlState = AVLState();
    _hashState = hashState();
    // * Raylib/Raygui initialization
    srand(time(NULL));
    DrawUtility::init();
    AppMenu::init();
    SLLScene::setSpecs(0.05f);
    SLLScene::init();

    Animation::setUpdateRate(5.f);
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
        // switch ( state )
        // {
        //     case MENU:
        //     {
        //         if (GuiButton((Rectangle){10, 10, 100, 50}, "Trie")) {
        //             state = TRIE;
        //         }
        //         if (GuiButton((Rectangle){10, 70, 100, 50}, "AVL")) {
        //             state = AVL;
        //         }
        //         if (GuiButton((Rectangle){10, 130, 100, 50}, "Hash")) {
        //             state = HASH_TABLE;
        //         }
        //         break;
        //     }
        //     case TRIE:
        //     {
        //         trieState.run();
        //         if (GuiButton((Rectangle){10, 10, 100, 50}, "Back")) {
        //             state = MENU;
        //         }
        //         break;
        //     }
        //     case AVL:
        //     {
        //         avlState.run();
        //         if (GuiButton((Rectangle){10, 10, 100, 50}, "Back")) {
        //             state = MENU;
        //         }
        //         break;
        //     }
        //     case HASH_TABLE:
        //     {
        //         _hashState.printTable();
        //         _hashState.run();
        //         if (GuiButton((Rectangle){10, 10, 100, 50}, "Back")) {
        //             state = MENU;
        //         }
        //         break;
        //     }
        // }
        Loop::render();
        EndDrawing();
    }
    std::cout << "Program ran successfully\n";
    UnloadFont(font);
    CloseWindow();
}