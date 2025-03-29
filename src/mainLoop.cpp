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
            renderFunc = &mScene::runAVL;
        }
        if (WelcomeMenu::isGraphPressed()) {
            currentScene = SceneList::GRAPH;
            renderFunc = &GraphScene::render;
            updateFunc = &GraphScene::update;

            recordFunc = &GraphScene::registerInput;
            AppMenu::highlightValue = &GraphScene::currentHighlighting;
        }
        if (WelcomeMenu::isHashTablePressed()) {
            currentScene = SceneList::HASH;
            renderFunc = &mScene::runHash;
        }
        if (WelcomeMenu::isLinkedListPressed()) {
            currentScene = SceneList::LINKED_LIST;

            renderFunc = &SLLScene::render;
            updateFunc = &SLLScene::update;
            recordFunc = &SLLScene::recordInput;
            AppMenu::highlightValue = &SLLScene::highlightedRow;
        }
        if (WelcomeMenu::isTriePressed()) {
            currentScene = TRIE;
            renderFunc = &mScene::runTrie;
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
        if (currentScene == SceneList::AVL || currentScene == SceneList::HASH || currentScene == SceneList::TRIE) ;
        else DrawRectangleLines(UPPER_LEFT.x, UPPER_LEFT.y, LOWER_RIGHT.x - UPPER_LEFT.x, LOWER_RIGHT.y - UPPER_LEFT.y, BLUE);
        AppMenu::render();
        MenuTable::render();
        if (renderFunc) renderFunc();
    }
    
}

}  // namespace Loop