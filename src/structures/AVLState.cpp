#include "AVLState.hpp"
#include "raygui.h"
#include "Utility.hpp"
#include <cstring>

const int MAX_TEXT_LENGTH = 10;

AVLState::AVLState() {
    mAVL = AVL();
    showOptions = false;
    showCreateOptions = false;
    showTextBox = false;
    editMode = false;
    textDestionation = 0;
    textBox[0] = '\0';
    requestText[0] = '\0';
    mTime = 0;
}

void AVLState::handleInput() {
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
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){10 + 50 + 400, 625, 40, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) mLib::GenerateRandomText(textBox);
        if ((CheckCollisionPointRec(GetMousePosition(), (Rectangle){10 + 50 + 440, 625, 40, 40}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        || GetKeyPressed() == KEY_ENTER) 
        {
            strcpy(requestText, textBox);
            textBox[0] = '\0';
            editMode = 0;
            if (requestText[0] != '\0') 
            {
                if (textDestionation == 1) mAVL.searchAnimation(requestText);
                if (textDestionation == 2) mAVL.insertAnimation(requestText);
                if (textDestionation == 3) mAVL.deleteAnimation(requestText);
            }
        }
    }
}

void AVLState::update() {
    if (editMode) {
        if (strlen(textBox) == 0) ;
        else
            if ('A' <= textBox[strlen(textBox) - 1] && textBox[strlen(textBox) - 1] <= 'Z') ;
            else
                if ('a' <= textBox[strlen(textBox) - 1] && textBox[strlen(textBox) - 1] <= 'z') textBox[strlen(textBox) - 1] -= 32;
                else textBox[strlen(textBox) - 1] = '\0';
    }
    mAVL.move(mAVL.root);
    mAVL.move(mAVL.root);
    mAVL.move(mAVL.root);
    mAVL.move(mAVL.root);
    mAVL.move(mAVL.root);
    mAVL.moveItr();
    mAVL.moveItr();   
    mAVL.moveItr();
    mAVL.moveItr();
}

void AVLState::render() {
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
    mAVL.drawLine(mAVL.root, 800, 100);
    mAVL.drawItr(800, 100);
    mAVL.draw(mAVL.root, 800, 100);
    mAVL.drawText(mAVL.root, 800, 100);
    mTime += GetFrameTime();
    if (mAVL.itr1 < mAVL.working.size())
    {
        if (mAVL.itr2 < mAVL.working[mAVL.itr1].second.size())
        {
            switch (mAVL.working[mAVL.itr1].first)
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
        if (mAVL.itr1 < mAVL.working.size())
        {
            if (mAVL.itr2 < mAVL.working[mAVL.itr1].second.size())
            {
                if (mAVL.move(mAVL.root) == 0 && mAVL.moveItr() == 0)
                {
                    auto current = mAVL.working[mAVL.itr1].second[mAVL.itr2];
                    if (current.first == SELECTING)
                    {
                        current.second->selected = true;
                    }
                    else if (current.first == CREATE) 
                    {
                        current.second->valid = true;
                        mAVL.calcPosition(mAVL.root);
                    }
                    else if (current.first == CLEAR)
                    {
                        current.second->selected = false;
                    }
                    else if (current.first == SET_ITR_INSTANCE)
                    {
                        mAVL.Itr[mAVL.itr1].first = mAVL.Itr[mAVL.itr1].second = mAVL.getPos(mAVL.root, current.second, 0, 0);
                    }
                    else if (current.first == SET_ITR_ANIMATION)
                    {
                        mAVL.Itr[mAVL.itr1].first = mAVL.getPos(mAVL.root, current.second, 0, 0);
                        mAVL.Itr[mAVL.itr1].second 
                            = mAVL.getPos(mAVL.root, mAVL.working[mAVL.itr1].second[mAVL.itr2 + 1].second, 0, 0);
                        mAVL.itr2 ++;
                    }
                    else if (current.first == DELETE_ITR)
                    {
                        mAVL.Itr[mAVL.itr1].first = mAVL.Itr[mAVL.itr1].second = {-1, -1};
                    }
                    else if (current.first == DELETE)
                    {
                        mAVL.deleteNode(mAVL.root, current.second);
                        mAVL.calcPosition(mAVL.root);
                    }
                    mAVL.itr2++;
                }
            }
            else 
                {
                    mAVL.itr1++;
                    mAVL.itr2 = 0;
                }
        }
    }
}