#include "TrieState.hpp"
#include "raygui.h"
#include <cstring>

const int MAX_TEXT_LENGTH = 10;

void GenerateRandomText(char *text) {
    int length = GetRandomValue(1, 10) % (MAX_TEXT_LENGTH + 1);
    for (int i = 0; i < length; i++) {
        text[i] = (GetRandomValue(1, 1000000000) % 26) + 'A';  
    }
    text[length] = '\0'; 
}

TrieState::TrieState() {
    mTrie = Trie();
    showOptions = false;
    showCreateOptions = false;
    showTextBox = false;
    editMode = false;
    textDestionation = 0;
    textBox[0] = '\0';
    requestText[0] = '\0';
    mTime = 0;
}

void TrieState::handleInput() {
    if (GuiButton((Rectangle){10, 550, 30, 200}, ">")) {
        showOptions = !showOptions;
        if (showOptions == 0) 
        {
            showCreateOptions = 0;
            showTextBox = 0;
        }
    }
    if (showOptions) {
        if (GuiButton((Rectangle){10 + 50, 550, 100, 40}, "Create")) {
            showCreateOptions = !showCreateOptions;
            showTextBox = 0;
        }
        if (GuiButton((Rectangle){10 + 50, 600, 100, 40}, "Search")) {
            showTextBox = 1;
            textDestionation = 1;
            showCreateOptions = 0;
        }
        if (GuiButton((Rectangle){10 + 50, 650, 100, 40}, "Insert")) {
            showTextBox = 1;
            textDestionation = 2;
            showCreateOptions = 0;
        }
        if (GuiButton((Rectangle){10 + 50, 700, 100, 40}, "Delete")) {
            showTextBox = 1;
            textDestionation = 3;
            showCreateOptions = 0;
        }
    }
    if (showCreateOptions)
    {
        if (GuiButton((Rectangle){10 + 50 + 150, 575, 100, 40}, "Clear")) {
        }
        if (GuiButton((Rectangle){10 + 50 + 150, 625, 100, 40}, "Random")) {
        }
        if (GuiButton((Rectangle){10 + 50 + 150, 675, 100, 40}, "Custom")) {
        }
    }
    if (showTextBox) {
        if (GuiTextBox((Rectangle){10 + 50 + 150, 625, 200, 40}, textBox, MAX_TEXT_LENGTH, editMode)) editMode = !editMode;
    }
    if (showTextBox) {
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){10 + 50 + 400, 625, 40, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) GenerateRandomText(textBox);
        if ((CheckCollisionPointRec(GetMousePosition(), (Rectangle){10 + 50 + 440, 625, 40, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        || GetKeyPressed() == KEY_ENTER) 
        {
            strcpy(requestText, textBox);
            textBox[0] = '\0';
            editMode = 0;
            if (textDestionation == 1) mTrie.searchAnimation(requestText);
            if (textDestionation == 2) mTrie.insertAnimation(requestText);
            //if (textDestionation == 3) mTrie.remove(requestText);
        }
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
    mTrie.move(mTrie.root);
    mTrie.move(mTrie.root);
    mTrie.move(mTrie.root);
    mTrie.move(mTrie.root);
    mTrie.move(mTrie.root);
    mTrie.move(mTrie.root);
    mTrie.move(mTrie.root);
    mTrie.moveItr();
    mTrie.moveItr();   
    mTrie.moveItr();
    mTrie.moveItr();
    mTrie.moveItr();
    mTrie.moveItr();
    mTrie.moveItr();
}

void TrieState::render() {
    if (showTextBox)
    {
        if (textDestionation == 1) DrawText("Searching", 10 + 50 + 150, 550, 20, BLACK);
        else if (textDestionation == 2) DrawText("Inserting", 10 + 50 + 150, 550, 20, BLACK);
        else if (textDestionation == 3) DrawText("Deleting", 10 + 50 + 150, 550, 20, BLACK);
        DrawRectangle(10 + 50 + 400, 625, 40, 40, Fade(RED, 0.3f));
        DrawRectangle(10 + 50 + 440, 625, 40, 40, Fade(GREEN, 0.3f));
        DrawText("RD", 10 + 50 + 400 + 10, 625 + 10, 20, BLACK);
        DrawText("GO", 10 + 50 + 440 + 10, 625 + 10, 20, BLACK);
    }
    mTrie.drawLine(mTrie.root, 700, 100);
    mTrie.drawItr(700, 100);
    mTrie.draw(mTrie.root, 700, 100);
    mTrie.drawText(mTrie.root, 700, 100);
    mTime += GetFrameTime();
    if (mTrie.itr1 < mTrie.working.size())
    {
        if (mTrie.itr2 < mTrie.working[mTrie.itr1].second.size())
        {
            switch (mTrie.working[mTrie.itr1].first)
            {
                case 1 : DrawText("Searching", 250, 10, 20, BLACK); break;
                case 2 : DrawText("Inserting", 250, 10, 20, BLACK); break;
                case 3 : DrawText("Deleting", 250, 10, 20, BLACK); break;
            }
        }
    }
    if (mTime > 0.5f)
    {
        mTime = 0;
        if (mTrie.itr1 < mTrie.working.size())
        {
            if (mTrie.itr2 < mTrie.working[mTrie.itr1].second.size())
            {
                if (mTrie.move(mTrie.root) == 0 && mTrie.moveItr() == 0)
                {
                    auto current = mTrie.working[mTrie.itr1].second[mTrie.itr2];
                    if (current.first == SELECTING)
                    {
                        current.second->selected = true;
                    }
                    else if (current.first == CREATE) 
                    {
                        current.second->valid = true;
                        mTrie.calcPosition(mTrie.root);
                    }
                    else if (current.first == CLEAR)
                    {
                        current.second->selected = false;
                    }
                    else if (current.first == SETEND)
                    {
                        current.second->isEndOfWord = true;
                    }
                    else if (current.first == SET_ITR_INSTANCE)
                    {
                        mTrie.Itr[mTrie.itr1].first = mTrie.Itr[mTrie.itr1].second = mTrie.getPos(mTrie.root, current.second, 0, 0);
                    }
                    else if (current.first == SET_ITR_ANIMATION)
                    {
                        mTrie.Itr[mTrie.itr1].second = mTrie.getPos(mTrie.root, current.second, 0, 0);
                    }
                    else if (current.first == DELETE_ITR)
                    {
                        mTrie.Itr[mTrie.itr1].first = mTrie.Itr[mTrie.itr1].second = {-1, -1};
                    }
                    mTrie.itr2++;
                }
            }
            else 
                {
                    mTrie.itr1++;
                    mTrie.itr2 = 0;
                }
        }
    }
}