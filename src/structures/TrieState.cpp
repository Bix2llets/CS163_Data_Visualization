#include "TrieState.hpp"
#include "raygui.h"
#include <mLib/Utility.hpp>
#include <cstring>
#include <fstream>
#include <mLib/tinyfiledialogs.h>

const int MAX_TEXT_LENGTH = 5;

#include <iostream>

TrieState::TrieState() : mTrie() {
    showOptions = false;
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
    forward = 0;
    backward = 0;
    sliderValue = 50;
}

TrieState::~TrieState() {
}

void TrieState::handleInput() {
    if (GuiButton((Rectangle){10, 700, 30, 190}, ">")) {
        showOptions = !showOptions;
        if (showOptions == 0) 
        {
            showCreateOptions = 0;
            showTextBox = 0;
        }
    }
    if (showOptions) {
        if (GuiButton((Rectangle){10 + 50, 700, 100, 40}, "Create")) {
            showCreateOptions = !showCreateOptions;
            showTextBox = 0;
        }
        if (GuiButton((Rectangle){10 + 50, 750, 100, 40}, "Search")) {
            showTextBox = 1;
            textDestionation = 1;
            showCreateOptions = 0;
        }
        if (GuiButton((Rectangle){10 + 50, 800, 100, 40}, "Insert")) {
            showTextBox = 1;
            textDestionation = 2;
            showCreateOptions = 0;
        }
        if (GuiButton((Rectangle){10 + 50, 850, 100, 40}, "Delete")) {
            showTextBox = 1;
            textDestionation = 3;
            showCreateOptions = 0;
        }
    }
    if (showCreateOptions & mTrie.completedAllActions())
    {
        if (GuiButton((Rectangle){10 + 50 + 150, 700, 100, 40}, "Clear")) {
            mTrie = Trie();
        }
        if (GuiButton((Rectangle){10 + 50 + 150, 750, 100, 40}, "Random")) {
            mTrie = Trie();
            for (int i = 0; i < GetRandomValue(0, 5); i ++)  {
                mLib::GenerateRandomText(requestText);
                mTrie.insert(requestText);
            }
        }
        if (GuiButton((Rectangle){10 + 50 + 150, 800, 100, 40}, "Custom")) {
            mTrie = Trie();
            const char *filter[2] = {"*.txt", "*.inp"};
            const char *path = tinyfd_openFileDialog("Open File", "", 2, filter, "txt or inp files", 0);
            std::cout << "File path: " << path << std::endl;
            std::cout << path << std::endl;
            if (path != NULL) {
                std::ifstream file(path);
                std::string line;
                while (std::getline(file, line)) mTrie.insert(line);
            }
        }
    }
    if (showTextBox & mTrie.completedAllActions()) {
        if (GuiTextBox((Rectangle){10 + 50 + 150, 800, 200, 40}, textBox, MAX_TEXT_LENGTH + 1, editMode)) editMode = !editMode;
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){10 + 50 + 400, 800, 40, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) mLib::GenerateRandomText(textBox);
        if ((CheckCollisionPointRec(GetMousePosition(), (Rectangle){10 + 50 + 440, 800, 40, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        || GetKeyPressed() == KEY_ENTER) 
        {
            strcpy(requestText, textBox);
            textBox[0] = '\0';
            editMode = 0;
            if (strlen(requestText) > 0) {
                if (textDestionation == 1) mTrie.search(requestText);
                if (textDestionation == 2) mTrie.insert(requestText);
                if (textDestionation == 3) mTrie.remove(requestText);
            }
        }
    }
    if (GuiButton((Rectangle){10 + 50 + 750, 800, 100, 40}, animationPlaying ? "Pause" : "Play")) {
        if (animationPlaying == 0) animationPlaying = 1;
        else {
            if (mTrie.completedAllActions()) animationPlaying = 0;
            else pendingPause = 1;
        }
    }
    if (showRunStepByStep && animationPlaying == 0) ;
    else GuiDisable();

    if (mTrie.startLoop()) GuiDisable();
    if (GuiButton((Rectangle){10 + 50 + 750 - 100, 800, 100, 40}, "Prev")) {
        isReversed = 1;
    }
    if (mTrie.startLoop()) GuiEnable();
    if (mTrie.endLoop()) GuiDisable();
    if (GuiButton((Rectangle){10 + 50 + 750 + 100, 800, 100, 40}, "Next")) {
        isReversed = 0;
    }
    if (mTrie.endLoop()) GuiEnable();

    if (showRunStepByStep && animationPlaying == 0) ;
    else GuiEnable();

    if (mTrie.endLoop()) GuiDisable();
    if (GuiButton((Rectangle){10 + 50 + 750 + 200, 800, 100, 40}, "Forward")) {
        forward = 1;
        mTimeStep = 1e-15;
        isReversed = 0;
    }
    if (mTrie.endLoop()) GuiEnable();
    if (mTrie.startLoop()) GuiDisable();
    if (GuiButton((Rectangle){10 + 50 + 750 - 200, 800, 100, 40}, "Backward")) {
        backward = 1;
        mTimeStep = 1e-15;
        isReversed = 1;
    }
    if (mTrie.startLoop()) GuiEnable();
    
    if (mTimeStep >= 0.1f) {
        float minValue = 0.0f;     
        float maxValue = 100.0f;   
        float newMin = 0.1f;
        float newMax = 2.0f;
        GuiSliderBar((Rectangle){10 + 50 + 750, 850, 200, 20}, "Time Step", TextFormat("%.2f", mTimeStepSlider), &sliderValue, minValue, maxValue);
        mTimeStepSlider = newMin + (newMax - newMin) * (sliderValue - minValue) / (maxValue - minValue);
        mTimeStep = 2.0f - mTimeStepSlider + 0.1f;
    }
}

void TrieState::update() {
    if (editMode) {
        if (strlen(textBox) == 0) ;
        else
            if ('A' <= textBox[strlen(textBox) - 1] && textBox[strlen(textBox) - 1] <= 'Z') ;
            else
                if ('a' <= textBox[strlen(textBox) - 1] && textBox[strlen(textBox) - 1] <= 'z') textBox[strlen(textBox) - 1] -= 32;
                else textBox[strlen(textBox) - 1] = '\0';
    }
    showRunStepByStep = mTrie.completeAnimation();
}

void TrieState::render() {
    if (showTextBox & mTrie.completedAllActions())
    {
        if (textDestionation == 1) DrawTextEx(mLib::mFont, "Searching", (Vector2) {10 + 50 + 150, 750}, 30, 2, BLACK);
        else if (textDestionation == 2) DrawTextEx(mLib::mFont, "Inserting", (Vector2) {10 + 50 + 150, 750}, 30, 2, BLACK);
        else if (textDestionation == 3) DrawTextEx(mLib::mFont, "Deleting", (Vector2) {10 + 50 + 150, 750}, 30, 2, BLACK);
        DrawRectangle(10 + 50 + 400, 800, 40, 40, Fade(RED, 0.3f));
        DrawRectangle(10 + 50 + 440, 800, 40, 40, Fade(GREEN, 0.3f));
        DrawTextEx(mLib::mFont, "RD", (Vector2) {10 + 50 + 400, 800}, 30, 2, BLACK);
        DrawTextEx(mLib::mFont, "GO", (Vector2) {10 + 50 + 440, 800}, 30, 2, BLACK);
    }
    mTrie.draw();
}

void TrieState::run() {
    handleInput();
    mTime += GetFrameTime();
    update();
    mTrie.update(mTime, mTimeStep);
    if (mTime >= mTimeStep && (animationPlaying || isReversed != -1)) {
        mTime = 0;
        if (isReversed == -1)
        {
            if (mTrie.Action(0))
            {
                showRunStepByStep = 1;
                if (pendingPause) {
                    pendingPause = 0;
                    animationPlaying = 0;
                }
            }
        }
        else
        {
            if (mTrie.Action(isReversed)) {
                if (forward) {
                    if (mTrie.reachedEnd()) {
                        forward = 0;
                        mTimeStep = 0.5f;
                        isReversed = -1;
                    }
                }
                else
                    if (backward) {
                        if (mTrie.reachedStart()) {
                            mTrie.ClearOperator();
                            backward = 0;
                            mTimeStep = 0.5f;
                            isReversed = -1;
                        }
                    }
                    else {
                        if (isReversed == 1 && mTrie.reachedStart()) mTrie.ClearOperator();
                        isReversed = -1;
                    }
            }
        }
    }
    render();
}