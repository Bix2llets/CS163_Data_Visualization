#include "mainLoop.h"

#include <mLib/mScene.hpp>

#include "graphScene.h"

namespace Loop {
float elapsedSinceLastUpdate = 0.f;
int frameCount = 0;
const float DELTA_TIME = 1.0f / 60;
SceneList currentScene = SceneList::MAIN_MENU;
bool isRunning = true;

const Vector2 UPPER_LEFT = {50, 50};
const Vector2 LOWER_RIGHT = {1550, 650};
void (*renderFunc)() = nullptr;
void (*updateFunc)() = nullptr;
void (*recordFunc)() = nullptr;
void checkForReturn() {
    if (AppMenu::backButton.isPressed()) {
        currentScene = MAIN_MENU;
        updateFunc = nullptr;
        recordFunc = nullptr;
        MenuTable::addPane = nullptr;
        MenuTable::deletePane = nullptr;
        MenuTable::algoPane = nullptr;
        MenuTable::storagePane = nullptr;
    }
}
void update() {
    elapsedSinceLastUpdate += GetFrameTime();
    while (elapsedSinceLastUpdate > DELTA_TIME) {
        frameCount++;
        elapsedSinceLastUpdate -= DELTA_TIME;
    }
    while (frameCount) {
        if (updateFunc != nullptr && isRunning) updateFunc();
        frameCount--;
    }
}

void setColorPalette() {
    if (AppMenu::isDarkMode) {
        nodeColorSet = COLOR_SET_DARK;
        buttonColorSet = BUTTON_SET_DARK;
        backgroundSet = BACKGROUND_SET_DARK;
        paneBackground = TokyoNight::NIGHT_BLACK;
        nodeDragHighlight = TokyoNight::NIGHT_GREEN;
        AppMenu::colorModeButton.setText("Night mode");
        mLib::highlightColor = {0,100,0,255};
    } else {
        nodeColorSet = COLOR_SET_LIGHT;
        buttonColorSet = BUTTON_SET_LIGHT;
        backgroundSet = BACKGROUND_SET_LIGHT;
        paneBackground = GBLight::BACKGROUND1;
        nodeDragHighlight = GBLight::DARK_GREEN;
        AppMenu::colorModeButton.setText("Light mode");
        mLib::highlightColor = {128,239,128,255};
    }
}
void registerInput() {
    if (AppMenu::colorModeButton.isPressed()) {
        AppMenu::isDarkMode = !AppMenu::isDarkMode;
        setColorPalette();
    }
    if (currentScene == SceneList::MAIN_MENU) {
        if (WelcomeMenu::isAVLTreePressed()) {
            currentScene = SceneList::AVL;
            renderFunc = []() { mScene::avl.render(); };
            updateFunc = []() { mScene::avl.update(); };
            recordFunc = []() { mScene::avl.handleInput(); };

            MenuTable::addPane = &AVLState::addPane;
            MenuTable::deletePane = &AVLState::removePane;
            MenuTable::algoPane = &AVLState::algoPane;
            MenuTable::storagePane = &AVLState::storagePane;
        }
        if (WelcomeMenu::isGraphPressed()) {
            currentScene = SceneList::GRAPH;
            renderFunc = &GraphScene::render;
            updateFunc = &GraphScene::update;

            recordFunc = &GraphScene::registerInput;
            AppMenu::highlightValue = &GraphScene::currentHighlighting;

            MenuTable::addPane = &GraphScene::addPane;
            MenuTable::deletePane = &GraphScene::deletePane;
            MenuTable::algoPane = &GraphScene::algoPane;
            MenuTable::storagePane = &GraphScene::storagePane;
        }
        if (WelcomeMenu::isHashTablePressed()) {
            currentScene = SceneList::HASH;
            renderFunc = []() { mScene::hash.render(); };
            updateFunc = []() { mScene::hash.update(); };
            recordFunc = []() { mScene::hash.handleInput(); };

            MenuTable::addPane = &HashState::addPane;
            MenuTable::deletePane = &HashState::removePane;
            MenuTable::algoPane = &HashState::algoPane;
            MenuTable::storagePane = &HashState::storagePane;
        }
        if (WelcomeMenu::isLinkedListPressed()) {
            currentScene = SceneList::LINKED_LIST;

            renderFunc = &SLLScene::render;
            updateFunc = &SLLScene::update;
            recordFunc = &SLLScene::recordInput;

            MenuTable::addPane = &SLLScene::addPane;
            MenuTable::deletePane = &SLLScene::deletePane;
            MenuTable::algoPane = &SLLScene::algoPane;
            MenuTable::storagePane = &SLLScene::miscPane;
            AppMenu::highlightValue = &SLLScene::highlightedRow;
        }
        if (WelcomeMenu::isTriePressed()) {
            currentScene = TRIE;
            renderFunc = []() { mScene::trie.render(); };
            updateFunc = []() { mScene::trie.update(); };
            recordFunc = []() { mScene::trie.handleInput(); };

            MenuTable::addPane = &TrieState::addPane;
            MenuTable::deletePane = &TrieState::removePane;
            MenuTable::algoPane = &TrieState::algoPane;
            MenuTable::storagePane = &TrieState::storagePane;
        }
        return;
    }
    checkForReturn();

    if (recordFunc) recordFunc();
}

void render() {
    DrawText(std::to_string(GetFPS()).c_str(), 1000, 10, 20, GREEN);
    if (currentScene == SceneList::MAIN_MENU) {
        WelcomeMenu::render();
    } else {
        ClearBackground(backgroundSet.backgroundNormal);
        DrawRectangle(UPPER_LEFT.x, UPPER_LEFT.y, LOWER_RIGHT.x - UPPER_LEFT.x,
                      LOWER_RIGHT.y - UPPER_LEFT.y,
                      backgroundSet.backgroundHighlight);
        if (renderFunc) renderFunc();
        DrawRectangleLinesEx(
            {UPPER_LEFT.x, UPPER_LEFT.y, LOWER_RIGHT.x - UPPER_LEFT.x,
             LOWER_RIGHT.y - UPPER_LEFT.y},
            3.0f, backgroundSet.borderNormal);
        // * For covering
        DrawRectangle(0, LOWER_RIGHT.y, GetRenderWidth(), GetRenderHeight(),
                      backgroundSet.backgroundNormal);
        DrawRectangle(LOWER_RIGHT.x, 0, GetRenderWidth() - LOWER_RIGHT.x,
                      GetRenderHeight(), backgroundSet.backgroundNormal);
        DrawRectangle(0, 0, GetRenderWidth(), UPPER_LEFT.y,
                      backgroundSet.backgroundNormal);
        DrawRectangle(0, 0, UPPER_LEFT.x, GetRenderHeight(),
                      backgroundSet.backgroundNormal);
        AppMenu::render();
        MenuTable::render();
    }
    AppMenu::colorModeButton.render();
}

}  // namespace Loop