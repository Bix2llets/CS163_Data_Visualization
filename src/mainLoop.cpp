#include "mainLoop.h"

#include "graphScene.h"
#include "raygui.h"

namespace Loop {
float elapsedSinceLastUpdate = 0.f;
int frameCount = 0;
SceneList currentScene = SceneList::MAIN_MENU;
bool isRunning = true;

void (*renderFunc)() = nullptr;
void (*updateFunc)() = nullptr;
void (*recordFunc)() = nullptr;
void checkForReturn() {
    if (CodePane::backButton.isPressed()) {
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
    while (elapsedSinceLastUpdate > AppInfo::DELTA_TIME) {
        frameCount++;
        elapsedSinceLastUpdate -= AppInfo::DELTA_TIME;
    }
    while (frameCount) {
        if (updateFunc != nullptr && isRunning) updateFunc();
        frameCount--;
    }
}

void setColorPalette() {
    if (CodePane::isDarkMode) {
        nodeColorSet = COLOR_SET_DARK;
        buttonColorSet = BUTTON_SET_DARK;
        backgroundSet = BACKGROUND_SET_DARK;
        paneBackground = TokyoNight::NIGHT_BLACK;
        nodeDragHighlight = TokyoNight::NIGHT_GREEN;
        sliderIndicator = TokyoNight::NIGHT_YELLOW;
        CodePane::colorModeButton.setText("Night mode");
        // Utility::highlightColor = GBLight::LIGHT_YELLOW;
        nodeResultColor = TokyoNight::NIGHT_RED;
        Utility::highlightColor = nodeColorSet.borderHighlight;
    } else {
        nodeColorSet = COLOR_SET_LIGHT;
        buttonColorSet = BUTTON_SET_LIGHT;
        backgroundSet = BACKGROUND_SET_LIGHT;
        paneBackground = GBLight::BACKGROUND1;
        nodeDragHighlight = GBLight::DARK_GREEN;
        sliderIndicator = GBLight::BACKGROUND4;
        CodePane::colorModeButton.setText("Light mode");
        // Utility::highlightColor = GBLight::LIGHT_GREEN;
        Utility::highlightColor = nodeColorSet.borderHighlight;
        nodeResultColor = GBLight::DARK_RED;
    }
}
void registerInput() {
    if (CodePane::colorModeButton.isPressed()) {
        CodePane::isDarkMode = !CodePane::isDarkMode;
        setColorPalette();
        configSlider();
    }
    if (currentScene == SceneList::MAIN_MENU) {
        if (WelcomeMenu::isAVLTreePressed()) {
            currentScene = SceneList::AVL;
            renderFunc = &AVLScene::render;
            updateFunc = &AVLScene::update;
            recordFunc = &AVLScene::handleInput;

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
            CodePane::highlightValue = &GraphScene::currentHighlighting;

            MenuTable::addPane = &GraphScene::addPane;
            MenuTable::deletePane = &GraphScene::deletePane;
            MenuTable::algoPane = &GraphScene::algoPane;
            MenuTable::storagePane = &GraphScene::storagePane;
        }
        if (WelcomeMenu::isHashTablePressed()) {
            currentScene = SceneList::HASH;
            renderFunc = &HashScene::render;
            updateFunc = &HashScene::update;
            recordFunc = &HashScene::handleInput;
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
            CodePane::highlightValue = &SLLScene::highlightedRow;
        }
        if (WelcomeMenu::isTriePressed()) {
            currentScene = TRIE;
            renderFunc = &TrieScene::render;
            updateFunc = &TrieScene::update;
            recordFunc = &TrieScene::handleInput;

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
        DrawRectangle(AppInfo::UPPER_LEFT.x, AppInfo::UPPER_LEFT.y,
                      AppInfo::LOWER_RIGHT.x - AppInfo::UPPER_LEFT.x,
                      AppInfo::LOWER_RIGHT.y - AppInfo::UPPER_LEFT.y,
                      backgroundSet.backgroundHighlight);
        if (renderFunc) renderFunc();
        DrawRectangleLinesEx({AppInfo::UPPER_LEFT.x, AppInfo::UPPER_LEFT.y,
                              AppInfo::LOWER_RIGHT.x - AppInfo::UPPER_LEFT.x,
                              AppInfo::LOWER_RIGHT.y - AppInfo::UPPER_LEFT.y},
                             3.0f, backgroundSet.borderNormal);
        // * For covering
        DrawRectangle(0, AppInfo::LOWER_RIGHT.y, GetRenderWidth(),
                      GetRenderHeight(), backgroundSet.backgroundNormal);
        DrawRectangle(AppInfo::LOWER_RIGHT.x, 0,
                      GetRenderWidth() - AppInfo::LOWER_RIGHT.x,
                      GetRenderHeight(), backgroundSet.backgroundNormal);
        DrawRectangle(0, 0, GetRenderWidth(), AppInfo::UPPER_LEFT.y,
                      backgroundSet.backgroundNormal);
        DrawRectangle(0, 0, AppInfo::UPPER_LEFT.x, GetRenderHeight(),
                      backgroundSet.backgroundNormal);
        CodePane::render();
        MenuTable::render();
    }
    CodePane::colorModeButton.render();
}

void configSlider() {
    GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL,
                ColorToInt(CodePane::buttonPalette->borderNormal));
    GuiSetStyle(SLIDER, BORDER_COLOR_FOCUSED,
                ColorToInt(CodePane::buttonPalette->borderNormal));
    GuiSetStyle(SLIDER, BORDER_COLOR_PRESSED,
                ColorToInt(CodePane::buttonPalette->borderNormal));
    GuiSetStyle(SLIDER, BORDER_WIDTH, 2);
    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL,
                ColorToInt(CodePane::buttonPalette->backgroundNormal));
    GuiSetStyle(SLIDER, BASE_COLOR_FOCUSED,
                ColorToInt(CodePane::buttonPalette->backgroundHighlight));
    GuiSetStyle(SLIDER, BASE_COLOR_PRESSED, ColorToInt(sliderIndicator));
    GuiSetStyle(SLIDER, TEXT_COLOR_NORMAL,
                ColorToInt(CodePane::buttonPalette->textNormal));
    GuiSetStyle(SLIDER, TEXT_COLOR_FOCUSED,
                ColorToInt(CodePane::buttonPalette->textHighlight));
    GuiSetStyle(SLIDER, TEXT_COLOR_PRESSED,
                ColorToInt(CodePane::buttonPalette->textHighlight));
}

}  // namespace Loop