#include "mainLoop.h"

namespace Loop {
float elapsedSinceLastUpdate = 0.f;
int frameCount = 0;
const float FRAME_TIME = 1.0f / 24;
SceneList currentScene = SceneList::MAIN_MENU;

void (*renderFunc)() = nullptr;
void (*updateFunc)() = nullptr;
void checkForReturn() {
    if (AppMenu::backButton.isPressed()) {
        currentScene = MAIN_MENU;
        for (std::vector<Button> buttonRow : AppMenu::buttonPanel)
            for (Button button : buttonRow) button.enable();

        AppMenu::locationBox.enable();
        AppMenu::valueBox.enable();
        renderFunc = nullptr;
        updateFunc = nullptr;
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
    switch (currentScene) {
        // Button configuration
        case MAIN_MENU: {
            if (WelcomeMenu::isAVLTreePressed()) currentScene = SceneList::AVL;
            if (WelcomeMenu::isGraphPressed()) currentScene = SceneList::GRAPH;
            if (WelcomeMenu::isHashTablePressed())
                currentScene = SceneList::HASH;
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
            }
            if (WelcomeMenu::isTriePressed()) currentScene = TRIE;
            break;
        }
        case LINKED_LIST: {
            checkForReturn();
            auto location = AppMenu::locationBox.getValue();
            auto value = AppMenu::valueBox.getValue();
            auto &buttonPanel = AppMenu::buttonPanel;
            if (buttonPanel[0][0].isPressed()) { 
                // * Add at end
                if (value.first) 
                {
                    SLLScene::addEnd(std::to_string(value.second));
                    AppMenu::loadCode(SLLScene::PSEUDO_INSERT_END);
                }
            }

            break;
        }
        case TRIE: {
            checkForReturn();
            break;
        }
        case GRAPH: {
            checkForReturn();
            break;
        }
        case AVL: {
            checkForReturn();
            break;
        }
        case HASH: {
            checkForReturn();
            break;
        }
        default:
            break;
    }
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