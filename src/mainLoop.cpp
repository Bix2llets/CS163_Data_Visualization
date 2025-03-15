#include "mainLoop.h"

namespace Loop {
float elapsedSinceLastUpdate = 0.f;
int frameCount = 0;
const float FRAME_TIME = 1.0f / 24;
SceneList currentScene = SceneList::MAIN_MENU;

void checkForReturn() {
    if (AppMenu::backButton.isPressed()) {
        currentScene = MAIN_MENU;
    }
}
void update() {
    elapsedSinceLastUpdate += GetFrameTime();
    while (elapsedSinceLastUpdate > FRAME_TIME) {
        frameCount++;
        elapsedSinceLastUpdate -= FRAME_TIME;
    }
    while (frameCount) {
        switch (currentScene) {
            case LINKED_LIST: {
                SLLScene::update();
                break;
            }
            case TRIE: {
                break;
            }
            case GRAPH: {
                break;
            }
            case AVL: {
                break;
            }
            case HASH: {
                break;
            }
            default: {
                break;
            }
        }
        frameCount--;
    }
}

void registerInput() {
    switch (currentScene) {
        case MAIN_MENU: {
            if (WelcomeMenu::isAVLTreePressed()) currentScene = SceneList::AVL;
            if (WelcomeMenu::isGraphPressed()) currentScene = SceneList::GRAPH;
            if (WelcomeMenu::isHashTablePressed())
                currentScene = SceneList::HASH;
            if (WelcomeMenu::isLinkedListPressed())
                currentScene = SceneList::LINKED_LIST;
            if (WelcomeMenu::isTriePressed()) currentScene = TRIE;
            break;
        }
        case LINKED_LIST: {
            checkForReturn();
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
        switch (currentScene) {
            case LINKED_LIST: {
                break;
            }
            case TRIE: {
                break;
            }
            case GRAPH: {
                break;
            }
            case AVL: {
                break;
            }
            case HASH: {
                break;
            }
            default:
                break;
        }
    }
}
}  // namespace Loop