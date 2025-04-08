#include "TrieState.hpp"
#include "menu.hpp"
#include <colorPalette.h>
#include <mLib/tinyfiledialogs.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <mLib/Utility.hpp>

#include "menuPane.h"
#include "raygui.h"

const int MAX_TEXT_LENGTH = 5;

#include <iostream>

double TrieState::mTimeStep;
TrieState::TrieState() : mTrie() {
    showCreateOptions = false;
    showTextBox = false;
    editMode = false;
    textDestionation = 0;
    textBox[0] = '\0';
    requestText[0] = '\0';
    mTime = 0;
    isReversed = -1;
    mTimeStep = 0.5f;
    animationPlaying = 1;
    pendingPause = 0;
    showRunStepByStep = 1;
    sliderValue = 50;
    // mCreateButton = new Button(10, 700, 200, 40, "Create", 20,
    // buttonPalette); mCreateButton->enable(); mSearchButton = new Button(10,
    // 740, 200, 40, "Search", 20, buttonPalette); mSearchButton->enable();
    // mInsertButton = new Button(10, 780, 200, 40, "Insert", 20,
    // buttonPalette); mInsertButton->enable(); mDeleteButton = new Button(10,
    // 820, 200, 40, "Delete", 20, buttonPalette); mDeleteButton->enable();
    // mClearButton = new Button(10 + 200, 700, 200, 40, "Clear", 20,
    // buttonPalette); mClearButton->enable(); mRandomButton = new Button(10 +
    // 200, 740, 200, 40, "Random", 20, buttonPalette); mClearButton->enable();
    // mCustomButton = new Button(10 + 200, 780, 200, 40, "Custom", 20,
    // buttonPalette); mCustomButton->enable(); mRandomValueButton = new
    // Button(10 + 200, 780, 200, 40, "Random word", 20, buttonPalette);
    // mRandomValueButton->enable();
    // mEnterButton = new Button(10 + 200, 820, 200, 40, "Enter", 20,
    // buttonPalette); mEnterButton->enable();
}

TrieState::~TrieState() {}

#include <cassert>

MenuPane TrieState::addPane({0, 0}, &GBLight::BACKGROUND1, &buttonColorSet,
                            &buttonColorSet);
MenuPane TrieState::removePane({0, 0}, &GBLight::BACKGROUND1, &buttonColorSet,
                               &buttonColorSet);
MenuPane TrieState::algoPane({0, 0}, &GBLight::BACKGROUND1, &buttonColorSet,
                             &buttonColorSet);
MenuPane TrieState::storagePane({0, 0}, &GBLight::BACKGROUND1, &buttonColorSet,
                                &buttonColorSet);

void TrieState::initPanes(Vector2 position) {
    addPane.setPosition(position);
    removePane.setPosition(position);
    algoPane.setPosition(position);
    storagePane.setPosition(position);

    addPane.newLine(0, 1, "Add", {"Word"}, {1}, true);
    addPane.newLine(1, 1, "Create", {"Num word"}, {0}, true);

    removePane.newLine(0, 1, "Remove", {"Word"}, {1}, false);
    removePane.newLine(1, 0, "Clear", {}, {}, false);

    algoPane.newLine(0, 1, "Search", {"Word"}, {1}, true);

    storagePane.newLine(0, 0, "Save", {}, {}, false);
    storagePane.newLine(1, 0, "Load", {}, {}, false);

    addPane.calibrate();
    removePane.calibrate();
    algoPane.calibrate();
    storagePane.calibrate();

    addPane.disable();
    removePane.disable();
    algoPane.disable();
    storagePane.disable();
}

void TrieState::handleInput() {
    assert(mLib::mFont.texture.id != 0);

    // if (mCreateButton->isPressed()) {
    //     showCreateOptions = !showCreateOptions;
    //     showTextBox = 0;
    // }
    // if (mSearchButton->isPressed()) {
    //     showTextBox = 1 - showTextBox;
    //     if (showTextBox) textDestionation = 1;
    //     else textDestionation = 0;
    //     showCreateOptions = 0;
    // }
    // if (mInsertButton->isPressed()) {
    //     showTextBox = 1 - showTextBox;
    //     if (showTextBox) textDestionation = 2;
    //     else textDestionation = 0;
    //     showCreateOptions = 0;
    // }
    // if (mDeleteButton->isPressed()) {
    //     showTextBox = 1 - showTextBox;
    //     if (showTextBox) textDestionation = 3;
    //     else textDestionation = 0;
    //     showCreateOptions = 0;
    // }
    // if (showCreateOptions & mTrie.completedAllActions())
    // {
    //     if (mClearButton->isPressed()) {
    //         mTrie = Trie();
    //     }
    //     if (mRandomButton->isPressed()) {
    //         mTrie = Trie();
    //         for (int i = 0; i < GetRandomValue(5, 10); i ++)  {
    //             mLib::GenerateRandomText(textBox);
    //             mTrie.insert(textBox);
    //             textBox[0] = '\0';
    //             while (mTrie.completedAllActions() == 0) {
    //                 mTrie.update(1e-15, 1e-15);
    //                 mTrie.Action(0);
    //             }
    //         }
    //     }
    //     if (mCustomButton->isPressed()) {
    //         const char *filter[2] = {"*.txt", "*.inp"};
    //         const char *path = tinyfd_openFileDialog("Open File", "", 2,
    //         filter, "txt or inp files", 0); std::cout << "File path: " <<
    //         path << std::endl; std::cout << path << std::endl; if (path !=
    //         NULL) {
    //             mTrie = Trie();
    //             std::ifstream file(path);
    //             std::string line;
    //             while (std::getline(file, line)) mTrie.insert(line);
    //         }
    //     }
    // }
    // if (showTextBox & mTrie.completedAllActions()) {
    //     if (GuiTextBox((Rectangle){10 + 200, 740, 200, 40}, textBox,
    //     MAX_TEXT_LENGTH + 1, editMode)) editMode = !editMode; if
    //     (mRandomValueButton->isPressed()) mLib::GenerateRandomText(textBox);
    //     if (mEnterButton->isPressed())
    //     {
    //         strcpy(requestText, textBox);
    //         textBox[0] = '\0';
    //         editMode = 0;
    //         if (strlen(requestText) > 0) {
    //             if (textDestionation == 1) mTrie.search(requestText);
    //             if (textDestionation == 2) mTrie.insert(requestText);
    //             if (textDestionation == 3) mTrie.remove(requestText);
    //         }
    //     }
    // }
    // if (GuiButton((Rectangle){660, 780, 120, 40}, animationPlaying ? "Pause"
    // : "Play")) {
    //     if (animationPlaying == 0) animationPlaying = 1;
    //     else {
    //         if (mTrie.completedAllActions()) animationPlaying = 0;
    //         else pendingPause = 1;
    //     }
    // }
    // if (showRunStepByStep && animationPlaying == 0) ;
    // else GuiDisable();

    // if (mTrie.startLoop()) GuiDisable();
    // if (GuiButton((Rectangle){660 - 120, 780, 120, 40}, "Prev")) {
    //     isReversed = 1;
    // }
    // if (mTrie.startLoop()) GuiEnable();
    // if (mTrie.endLoop()) GuiDisable();
    // if (GuiButton((Rectangle){660 + 120, 780, 120, 40}, "Next")) {
    //     isReversed = 0;
    // }
    // if (mTrie.endLoop()) GuiEnable();

    // if (showRunStepByStep && animationPlaying == 0) ;
    // else GuiEnable();

    // if (mTrie.endLoop()) GuiDisable();
    // if (GuiButton((Rectangle){660 + 240, 780, 120, 40}, "Forward")) {
    //     while (mTrie.completedAllActions() == 0) {
    //         mTrie.update(1e-15, 1e-15);
    //         mTrie.Action(0);
    //     }
    // }
    // if (mTrie.endLoop()) GuiEnable();
    // if (mTrie.startLoop()) GuiDisable();
    // if (GuiButton((Rectangle){660 - 240, 780, 120, 40}, "Backward")) {
    //     do {
    //         mTrie.update(1e-15, 1e-15);
    //         mTrie.Action(1);
    //     } while (mTrie.completedAllActions() == 0 && mTrie.reachedStart() ==
    //     0); mTrie.ClearOperator();
    // }
    // if (mTrie.startLoop()) GuiEnable();

    // if (mTimeStep >= 0.1f) {
    //     float minValue = 0.0f;
    //     float maxValue = 100.0f;
    //     float newMin = 0.1f;
    //     float newMax = 2.0f;
    //     GuiSliderBar((Rectangle){600, 850, 200, 20}, "Time Step",
    //     TextFormat("%.2f", mTimeStepSlider), &sliderValue, minValue,
    //     maxValue); mTimeStepSlider = newMin + (newMax - newMin) *
    //     (sliderValue - minValue) / (maxValue - minValue); mTimeStep = 2.0f -
    //     mTimeStepSlider + 0.1f;
    // }

    if (addPane.isButtonPressed(0)) {
        if (!mTrie.completedAllActions()) return;
        std::string word = addPane.getForm(0, 0).getText();
        addPane.getForm(0, 0).clear();
        if (word.empty()) return;
        mTrie.insert(word);
    }

    if (addPane.isRandomPressed(0)) {
        char randomWord[MAX_TEXT_LENGTH + 1];
        mLib::GenerateRandomText(randomWord);
        addPane.getForm(0, 0).setText(randomWord);
    }

    if (addPane.isRandomPressed(1)) {
        int size = GetRandomValue(1, 15);
        addPane.getForm(1, 0).setText(std::to_string(size));
    }

    if (addPane.isButtonPressed(1)) {
        mTrie = Trie();
        std::string data = addPane.getForm(1, 0).getText();
        addPane.getForm(1, 0).clear();
        int size;
        if (!isStrNum(data)) size = GetRandomValue(1, 15);
        else size = std::stoi(data);
        for (int i = 0; i < size; i++) {
            char randomWord[MAX_TEXT_LENGTH + 1];
            mLib::GenerateRandomText(randomWord);
            mTrie.insert(randomWord);
            while (!mTrie.completedAllActions()) {
                mTrie.update(1e-15, 1e-15);
                mTrie.Action(0);
            }
        }
        mTrie.setNULLPos(mTrie.getRoot());
        mTime = 0;
    }

    if (removePane.isButtonPressed(0)) {  // Remove operation
        if (!mTrie.completedAllActions()) return;

        std::string word = removePane.getForm(0, 0).getText();
        removePane.getForm(0, 0).clear();
        if (word.empty()) return;
        mTrie.remove(word);  // Perform the remove operation
    }

    if (removePane.isButtonPressed(1)) {  // Clear operation
        mTrie = Trie();                   // Reset the Trie
    }

    if (algoPane.isButtonPressed(0)) {
        std::string word = algoPane.getForm(0, 0).getText();
        algoPane.getForm(0, 0).clear();
        if (word.empty()) return;
        mTrie.search(word);
    }

    if (algoPane.isRandomPressed(0)) {
        if (!mTrie.completedAllActions()) return;

        char randomWord[MAX_TEXT_LENGTH + 1];
        mLib::GenerateRandomText(randomWord);
        algoPane.getForm(0, 0).setText(randomWord);
    }

    if (storagePane.isButtonPressed(0)) {
        const char *filePath = tinyfd_saveFileDialog("Save Trie", "trie.txt", 1,
                                                     (const char *[]){"*.txt"},
                                                     "Text files (*.txt)");
        if (filePath) {
            std::ofstream outFile(filePath);
            if (!outFile) {
                tinyfd_messageBox("Error", "Failed to open file for saving.",
                                  "ok", "error", 1);
                return;
            }
            std::vector<std::string> words = mTrie.getWords();
            for (const auto &word : words) {
                outFile << word << "\n";  // Write each word to the file
            }
            outFile.close();
        }
    }

    if (storagePane.isButtonPressed(1)) {
        const char *filePath = tinyfd_openFileDialog("Load Trie", "trie.txt", 1,
                                                     (const char *[]){"*.txt"},
                                                     "Text files (*.txt)", 0);
        if (filePath) {
            std::ifstream inFile(filePath);
            if (!inFile) {
                tinyfd_messageBox("Error", "Failed to open file for loading.",
                                  "ok", "error", 1);
                return;
            }
            mTrie = Trie();
            std::string line;
            while (std::getline(inFile, line)) {
                mTrie.insert(line);
                while (!mTrie.completedAllActions()) {
                    mTrie.update(1e-15, 1e-15);
                    mTrie.Action(0);
                }
            }
            inFile.close();
        }
    }
    if (MenuTable::prevButton.isPressed()) {  // Undo functionality
        MenuTable::pauseAnimation();
        //if (!mAVL.completeAnimation()) return;
        isReversed = 1;;
    }
    
    if (MenuTable::nextButton.isPressed()) {  // Redo functionality
        MenuTable::pauseAnimation();
        //if (!mAVL.completeAnimation()) return;
        isReversed = 0;
    }
    
    if (MenuTable::forwardButton.isPressed()) {  // Forward functionality
        MenuTable::pauseAnimation();
        while (!mTrie.completedAllActions()) {
            mTrie.update(1e-15, 1e-15);
            mTrie.Action(0);
        }
    }
    
    if (MenuTable::backwardButton.isPressed()) {  // Backward functionality
        MenuTable::pauseAnimation();
        do {
            mTrie.update(1e-15, 1e-15);
            mTrie.Action(1);
        } while (!mTrie.completedAllActions() && !mTrie.reachedStart());
        //mTrie.ClearOperator();
    }

    if (MenuTable::pauseButton.isPressed() || *MenuTable::isPlaying) animationPlaying = 1;
    if (MenuTable::playButton.isPressed() || !*MenuTable::isPlaying) {
        if (mTrie.completedAllActions()) animationPlaying = 0;
        else pendingPause = 1;
    }

    if (pendingPause || isReversed != -1) update();
}

void TrieState::update() {
    if (editMode) {
        if (strlen(textBox) == 0)
            ;
        else if ('A' <= textBox[strlen(textBox) - 1] &&
                 textBox[strlen(textBox) - 1] <= 'Z')
            ;
        else if ('a' <= textBox[strlen(textBox) - 1] &&
                 textBox[strlen(textBox) - 1] <= 'z')
            textBox[strlen(textBox) - 1] -= 32;
        else
            textBox[strlen(textBox) - 1] = '\0';
    }
    showRunStepByStep = mTrie.completeAnimation();

    mTrie.update(mTime, mTimeStep);
    if (mTime >= mTimeStep && (animationPlaying || isReversed != -1)) {
        mTime = 0;
        if (isReversed == -1) {
            if (mTrie.Action(0)) {
                showRunStepByStep = 1;
                if (pendingPause) {
                    pendingPause = 0;
                    animationPlaying = 0;
                }
            }
        } else {
            if (mTrie.Action(isReversed)) {
                if (isReversed == 1 && mTrie.reachedStart()) ;
                    //mTrie.ClearOperator();
                isReversed = -1;
            }
        }
    }
}

void TrieState::render() {
    mTime += GetFrameTime();
    if (showTextBox & mTrie.completedAllActions()) {
        if (textDestionation == 1)
            DrawTextEx(mLib::mFont, "Searching", (Vector2){10 + 250, 700}, 30,
                       2, WHITE);
        else if (textDestionation == 2)
            DrawTextEx(mLib::mFont, "Inserting", (Vector2){10 + 250, 700}, 30,
                       2, WHITE);
        else if (textDestionation == 3)
            DrawTextEx(mLib::mFont, "Deleting", (Vector2){10 + 250, 700}, 30, 2,
                       WHITE);
        mRandomValueButton->render();
        mEnterButton->render();
    }
    mTrie.draw();
    // mSearchButton->render();
    // mInsertButton->render();
    // mDeleteButton->render();
    // mCreateButton->render();
    // if (showCreateOptions & mTrie.completedAllActions()) {
    //     mClearButton->render();
    //     mRandomButton->render();
    //     mCustomButton->render();
    // }
    // DrawTextEx(mLib::mFont, mTrie.completedAllActions() ? "Animation
    // Completed" : animationPlaying ? "Animation Running" : "Animation Paused",
    // (Vector2) {1200, 10}, 30, 2, mTrie.completedAllActions() ? WHITE :
    // animationPlaying ? GREEN : RED);
}

void TrieState::run() {
    handleInput();
    update();

    render();
}

void TrieState::setAnimationSpeed(float factor) { mTimeStep = 1.0f / factor; }