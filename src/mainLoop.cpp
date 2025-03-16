#include "mainLoop.h"

namespace Loop {
float elapsedSinceLastUpdate = 0.f;
int frameCount = 0;
const float FRAME_TIME = 1.0f / 24;
SceneList currentScene = SceneList::MAIN_MENU;

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
        renderFunc = nullptr;
        updateFunc = nullptr;
        recordFunc = nullptr;
    }
}
void update() {
    elapsedSinceLastUpdate += GetFrameTime();
    while (elapsedSinceLastUpdate > FRAME_TIME) {
        frameCount++;
        elapsedSinceLastUpdate -= FRAME_TIME;
    }
    while (frameCount) {
        if (updateFunc != nullptr) updateFunc();
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
    if (recordFunc) recordFunc();
}

void render() {
    if (currentScene == SceneList::MAIN_MENU) {
        WelcomeMenu::render();
    } else {
        AppMenu::render();
        renderFunc();
    }
}

}  // namespace Loop