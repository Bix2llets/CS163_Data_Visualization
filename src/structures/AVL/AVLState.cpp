#include "avl/AVLState.hpp"
#include "menu.hpp"
#include <colorPalette.h>
#include <mLib/tinyfiledialogs.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include "Utility.h"

#include "menuPane.h"
#include "raygui.h"

const int MAX_TEXT_LENGTH = 3;

#include <iostream>

ColorSet const *AVLState::buttonPalette = &buttonColorSet;

MenuPane AVLState::addPane({0, 0}, &paneBackground, &buttonColorSet,
                           &buttonColorSet);
MenuPane AVLState::removePane({0, 0}, &paneBackground, &buttonColorSet,
                              &buttonColorSet);
MenuPane AVLState::algoPane({0, 0}, &paneBackground, &buttonColorSet,
                            &buttonColorSet);
MenuPane AVLState::storagePane({0, 0}, &paneBackground, &buttonColorSet,
                               &buttonColorSet);
double AVLState::mTimeStep;
AVLState::AVLState() : mAVL() {
    showCreateOptions = false;
    showTextBox = false;
    // editMode = false;
    // textDestionation = 0;
    // textBox[0] = '\0';
    // requestText[0] = '\0';
    mTime = 0;
    isReversed = -1;
    mTimeStep = 0.5f;
    animationPlaying = 1;
    pendingPause = 0;
    // showRunStepByStep = 1;
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
    // Button(10 + 200, 780, 200, 40, "Random value", 20, buttonPalette);
    // mRandomValueButton->enable();
    // mEnterButton = new Button(10 + 200, 820, 200, 40, "Enter", 20,
    // buttonPalette); mEnterButton->enable();
}

AVLState::~AVLState() {}

#include <cassert>

void AVLState::initPanes(Vector2 position) {
    addPane.setPosition(position);
    removePane.setPosition(position);
    algoPane.setPosition(position);
    storagePane.setPosition(position);
    addPane.newLine(0, 1, "Add", {"Value"}, {0}, true);
    addPane.newLine(1, 1, "Create", {"Size"}, {0}, true);

    removePane.newLine(0, 1, "Remove", {"Value"}, {0}, true);
    removePane.newLine(1, 0, "Clear", {}, {}, false);

    algoPane.newLine(0, 2, "Update", {"Old key", "New key"}, {0, 0}, true);
    algoPane.newLine(1, 1, "Search", {"Value"}, {0}, true);

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

void AVLState::handleInput() {
    assert(Utility::inter30.texture.id != 0);

    if (addPane.isButtonPressed(0)) {
        if (!mAVL.completedAllActions()) return;

        std::string data = addPane.getForm(0, 0).getText();
        addPane.getForm(0, 0).clear();
        if (!isStrNum(data)) return;
        mAVL.insert(std::stoi(data));
    }

    if (addPane.isRandomPressed(0)) {
        int randomValue = rand() % 1000;
        addPane.getForm(0, 0).setText(std::to_string(randomValue));
    }
    
    if (addPane.isRandomPressed(1)) {
        int size = GetRandomValue(1, 15);
        addPane.getForm(1, 0).setText(std::to_string(size));
    }
    
    if (addPane.isButtonPressed(1)) {  
        if (!mAVL.completedAllActions()) return;
        mAVL = AVL();
        std::string data = addPane.getForm(1, 0).getText();
        addPane.getForm(1, 0).clear();
        int size;
        if (!isStrNum(data)) size = GetRandomValue(1, 15);
        else size = std::stoi(data);
        //std::vector<int> values = {778, 808, 175, 316, 699, 457, 678, 246, 688};
        for (int i = 0; i < size; i++) {
            int x = GetRandomValue(0, 1000000000) % 1000;
            //x = values[i];
            mAVL.insert(x);
            while (mAVL.completedAllActions() == 0) {
                mAVL.update(1, 1);
                mAVL.Action(0);
            }
        }
        //mAVL.printDebug(mAVL.getRoot());
        mAVL.setNULLPos(mAVL.getRoot());
        mTime = 0;
    }

    if (removePane.isButtonPressed(0)) {
        if (!mAVL.completedAllActions()) return;
        
        std::string data = removePane.getForm(0, 0).getText();
        removePane.getForm(0, 0).clear();
        if (!isStrNum(data)) return;
        mAVL.remove(std::stoi(data));
    }

    if (removePane.isRandomPressed(0)) {
        std::vector<int> values;
        std::queue<AVLNode *> nodeQueue;
        AVLNode *root = mAVL.getRoot();
        if (root) nodeQueue.push(root);

        while (!nodeQueue.empty()) {
            AVLNode *current = nodeQueue.front();
            nodeQueue.pop();
            values.push_back(current->value);

            if (current->left) nodeQueue.push(current->left);
            if (current->right) nodeQueue.push(current->right);
        }
        if (values.size() == 0) return;
        int place = rand() % values.size();
        removePane.getForm(0, 0).setText(std::to_string(values[place]));
    }
    if (removePane.isButtonPressed(1)) {
        if (!mAVL.completedAllActions()) return;
        mAVL = AVL();
        return;
    }

    if (algoPane.isButtonPressed(0)) {
        if (!mAVL.completedAllActions()) return;
        std::string data1 = algoPane.getForm(0, 0).getText();
        std::string data2 = algoPane.getForm(0, 1).getText();
        algoPane.getForm(0, 0).clear();
        algoPane.getForm(0, 1).clear();
        if (!isStrNum(data1) || !isStrNum(data2)) return;
        mAVL.upOldNew(std::stoi(data1), std::stoi(data2));  // Perform the update operation
    }

    if (algoPane.isRandomPressed(0)) {  
        std::vector<int> values;
        std::queue<AVLNode *> nodeQueue;
        AVLNode *root = mAVL.getRoot();
        if (root) nodeQueue.push(root);

        while (!nodeQueue.empty()) {
            AVLNode *current = nodeQueue.front();
            nodeQueue.pop();
            values.push_back(current->value);

            if (current->left) nodeQueue.push(current->left);
            if (current->right) nodeQueue.push(current->right);
        }
        if (values.size() == 0) return;
        int place = rand() % values.size();
        algoPane.getForm(0, 0).setText(std::to_string(values[place]));
        int newKey = rand() % 1000;
        algoPane.getForm(0, 1).setText(std::to_string(newKey));
    }

    if (algoPane.isButtonPressed(1)) {  // Search functionality
        if (!mAVL.completedAllActions()) return;
        std::string data = algoPane.getForm(1, 0).getText();
        algoPane.getForm(1, 0).clear();
        if (!isStrNum(data)) return;
        int value = std::stoi(data);
        mAVL.search(value);  // Perform the search operation
        // while (mAVL.completedAllActions() == 0) {
        //     mAVL.update(1e-15, 1e-15);
        //     mAVL.Action(0);
        // }
    }

    if (algoPane.isRandomPressed(1)) {  // Random value assignment for algoPane
        int randomValue = rand() % 1000;  // Generate a random value
        algoPane.getForm(1, 0).setText(
            std::to_string(randomValue));  // Set the random value in the form
    }

    if (storagePane.isButtonPressed(0)) {  // Save functionality
        if (!mAVL.completedAllActions()) return;
        const char *filePath = tinyfd_saveFileDialog(
            "Save AVL Tree", "avltree.txt", 1, (const char *[]){"*.txt"},
            "Text files (*.txt)");
        if (filePath) {
            std::ofstream outFile(filePath);
            if (!outFile) {
                tinyfd_messageBox("Error", "Failed to open file for saving.",
                                  "ok", "error", 1);
                return;
            }
            std::vector<int> valueList;
            AVLNode *root = mAVL.getRoot();
            std::queue<AVLNode *> nodeList;
            nodeList.push(root);
            while (nodeList.size()) {
                AVLNode *curr = nodeList.front();
                nodeList.pop();

                valueList.push_back(curr->value);
                if (curr->left) nodeList.push(curr->left);
                if (curr->right) nodeList.push(curr->right);
            }

            //std::sort(valueList.begin(), valueList.end());
            for (int x : valueList) outFile << x << " ";
            outFile << "\n";
            outFile.close();
        }
    }

    if (storagePane.isButtonPressed(1)) {  // Load functionality
        if (!mAVL.completedAllActions()) return;
        const char *filePath = tinyfd_openFileDialog(
            "Load AVL Tree", "avltree.txt", 1, (const char *[]){"*.txt"},
            "Text files (*.txt)", 0);
        if (filePath) {
            std::ifstream inFile(filePath);
            if (!inFile) {
                tinyfd_messageBox("Error", "Failed to open file for loading.",
                                  "ok", "error", 1);
                return;
            }
            mAVL = AVL();  // Clear the current AVL tree
            int n;
            while (inFile >> n) {
                mAVL.insert(n);
                while (mAVL.completedAllActions() == 0) {
                    mAVL.update(1e-15, 1e-15);
                    mAVL.Action(0);
                }
            }
            inFile.close();
        }
    }
    // if (MenuTable::prevButton.isPressed()) {  // Undo functionality
    //     //if (!mAVL.completeAnimation()) return;
    //     MenuTable::pauseAnimation();
    //     isReversed = 1;;
    // }
    
    // if (MenuTable::nextButton.isPressed()) {  // Redo functionality
    //     //if (!mAVL.completeAnimation()) return;
    //     MenuTable::pauseAnimation();
    //     isReversed = 0;
    // }

    if (MenuTable::prevButton.isPressed()) {  // Undo functionality
        //if (!mAVL.completeAnimation()) return;
        // MenuTable::pauseAnimation();
        isReversed = 1;;
    }
    if (MenuTable::nextButton.isPressed()) {  // Redo functionality
        //if (!mAVL.completeAnimation()) return;
        if (*MenuTable::isPlaying) {
            while (true) {
                mAVL.update(1e-15, 1e-15);
                if (mAVL.Action(0)) break;
            }
        } else isReversed = 0;
    }

    if (MenuTable::forwardButton.isPressed()) {  // Forward functionality
        while (!mAVL.completedAllActions()) {
            mAVL.update(1e-15, 1e-15);
            mAVL.Action(0);
        }
    }

    if (MenuTable::backwardButton.isPressed()) {  // Backward functionality
        // MenuTable::pauseAnimation();
        do {
            mAVL.update(1e-15, 1e-15);
            mAVL.Action(1);
        } while (!mAVL.completedAllActions() && !mAVL.reachedStart());
        mAVL.ClearOperator();
    }

    if (MenuTable::pauseButton.isPressed() || *MenuTable::isPlaying) animationPlaying = 1;
    if (MenuTable::playButton.isPressed() || !*MenuTable::isPlaying) {
        if (mAVL.completedAllActions()) animationPlaying = 0;
        else pendingPause = 1;
    }

    if (pendingPause || isReversed != -1) update();
}

void AVLState::update() {
    mAVL.update(mTime, mTimeStep);
    if (mTime >= mTimeStep && (animationPlaying || isReversed != -1)) {
        mTime = 0;
        if (isReversed == -1) {
            if (mAVL.Action(0)) {
                //showRunStepByStep = 1;
                if (pendingPause) {
                    pendingPause = 0;
                    animationPlaying = 0;
                }
            }
        } else {
            if (mAVL.Action(isReversed)) {
                if (isReversed == 1 && mAVL.reachedStart()) ;
                //mAVL.ClearOperator();
                isReversed = -1;
            }
        }
    }
}

void AVLState::render() {
    mTime += GetFrameTime();
    mAVL.draw();
}

void AVLState::run() {
    handleInput();
    update();
    
    render();
}

void AVLState::setAnimationSpeed(float factor) {
    mTimeStep = 1.0f / factor;
}