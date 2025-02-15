#include "..\..\..\src\TrieState.hpp"
#include "raygui.h"
#include <cstring>

const int MAX_TEXT_LENGTH = 15;

TrieState::TrieState() {
    trie = Trie();
    showOptions = false;
    showCreateOptions = false;
    showTextBox = false;
    editMode = false;
    textDestionation = 0;
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
            showTextBox = !showTextBox;
            textDestionation = 1;
            showCreateOptions = 0;
        }
        if (GuiButton((Rectangle){10 + 50, 650, 100, 40}, "Insert")) {
            showTextBox = !showTextBox;
            textDestionation = 2;
            showCreateOptions = 0;
        }
        if (GuiButton((Rectangle){10 + 50, 700, 100, 40}, "Delete")) {
            showTextBox = !showTextBox;
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
        if (GuiTextBox((Rectangle){10 + 50 + 150, 600, 200, 40}, textBox, 15, editMode)) editMode = !editMode;
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
}

void TrieState::render() {
}