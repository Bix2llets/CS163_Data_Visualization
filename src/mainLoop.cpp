#include "mainLoop.h"
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
        for (std::vector<Button> &buttonRow : AppMenu::buttonPanel)
            for (Button &button : buttonRow) button.enable();

        AppMenu::locationBox.enable();
        AppMenu::valueBox.enable();
        AppMenu::undoButton.enable();
        AppMenu::redoButton.enable();
        AppMenu::togglePauseButton.enable();
        AppMenu::valueText.enable();
        AppMenu::locationText.enable();
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
        if (WelcomeMenu::isGraphPressed()) {
            currentScene = SceneList::GRAPH;

            AppMenu::buttonPanel[0][0].setText("Add Node");
            AppMenu::buttonPanel[1][0].setText("Remove Node");
            AppMenu::buttonPanel[0][1].setText("Add Edge");
            AppMenu::buttonPanel[1][1].setText("Remove Edge");
            AppMenu::buttonPanel[2][0].setText("MST");
            AppMenu::buttonPanel[2][1].setText("Shortest Path");
            
            AppMenu::locationBox.disable();
            AppMenu::locationText.disable();
            renderFunc = &GraphScene::render;
            updateFunc = &GraphScene::update;

            recordFunc = &GraphScene::registerInput;
            AppMenu::highlightValue = &GraphScene::currentHighlighting;
        }
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
    DrawText(std::to_string(GetFPS()).c_str(), 1000, 10, 20, GREEN);
    if (currentScene == SceneList::MAIN_MENU) {
        WelcomeMenu::render();
    } else {
        DrawRectangleLines(UPPER_LEFT.x, UPPER_LEFT.y, LOWER_RIGHT.x - UPPER_LEFT.x, LOWER_RIGHT.y - UPPER_LEFT.y, BLUE);
        AppMenu::render();
        if (renderFunc) renderFunc();
    }
}

}  // namespace Loop