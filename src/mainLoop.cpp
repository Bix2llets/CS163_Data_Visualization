#include "mainLoop.h"

namespace Loop {
float elapsedSinceLastUpdate = 0.f;
int frameCount = 0;
const float DELTA_TIME = 1.0f / 24;
SceneList currentScene = SceneList::MAIN_MENU;
bool isRunning = true;

void (*renderFunc)() = nullptr;
void (*updateFunc)() = nullptr;
void (*recordFunc)() = nullptr;
void checkForReturn() {
    if (AppMenu::backButton.isPressed()) {
        currentScene = MAIN_MENU;
        for (std::vector<Button> buttonRow : AppMenu::buttonPanel)
            for (Button button : buttonRow) button.enable();

        AppMenu::locationBox.enable();
        AppMenu::valueBox.enable();
        AppMenu::undoButton.enable();
        AppMenu::redoButton.enable();
        AppMenu::togglePauseButton.enable();
        renderFunc = nullptr;
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
        if (WelcomeMenu::isAVLTreePressed()) currentScene = SceneList::AVL;
        if (WelcomeMenu::isGraphPressed()) currentScene = SceneList::GRAPH;
        if (WelcomeMenu::isHashTablePressed()) currentScene = SceneList::HASH;
        if (WelcomeMenu::isLinkedListPressed()) {
            currentScene = SceneList::LINKED_LIST;

            AppMenu::buttonPanel[0][0].setText("Add End");
            AppMenu::buttonPanel[1][0].setText("Remove End");
            AppMenu::buttonPanel[0][1].setText("Add");
            AppMenu::buttonPanel[1][1].setText("Remove");
            AppMenu::buttonPanel[2][1].setText("Search");
            AppMenu::buttonPanel[2][0].disable();

            renderFunc = &SLLScene::render;
            updateFunc = &SLLScene::update;
            recordFunc = &SLLScene::recordInput;
            AppMenu::highlightValue = &SLLScene::highlightedRow;
        }
        if (WelcomeMenu::isTriePressed()) currentScene = TRIE;
        return;
    }
    checkForReturn();
    
    if (AppMenu::togglePauseButton.isPressed()) isRunning = !isRunning;
    if (isRunning) AppMenu::togglePauseButton.setText("Running");
    else AppMenu::togglePauseButton.setText("Pausing");

    
    if (recordFunc) recordFunc();
}

void render() {
    if (currentScene == SceneList::MAIN_MENU) {
        WelcomeMenu::render();
    } else {
        AppMenu::render();
        if (renderFunc) renderFunc();
    }
}

}  // namespace Loop