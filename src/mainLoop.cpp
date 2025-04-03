#include "mainLoop.h"
#include "graphScene.h"
#include <mLib/mScene.hpp>

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

void registerInput() {


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
        ClearBackground(GBDark::BACKGROUND0S);
        DrawRectangle(UPPER_LEFT.x, UPPER_LEFT.y, LOWER_RIGHT.x - UPPER_LEFT.x, LOWER_RIGHT.y - UPPER_LEFT.y, GBLight::BACKGROUND4);
        DrawRectangleLinesEx({UPPER_LEFT.x, UPPER_LEFT.y, LOWER_RIGHT.x - UPPER_LEFT.x, LOWER_RIGHT.y - UPPER_LEFT.y}, 3.0f, GBLight::FOREGROUND4);
        if (renderFunc) renderFunc();
        AppMenu::render();
        MenuTable::render();
    }
    
}

}  // namespace Loop