#ifndef TrieSTATE_HPP
#define TrieSTATE_HPP

#include "raylib.h"
#include <cstring>
#include "Trie.hpp"
#include "button.h"

class TrieState
{
    ColorSet const *buttonPalette = &BUTTON_SET_1;
    
    public:
        TrieState();
        void handleInput();
        void update();
        void render();
        void run();
        ~TrieState();
    private:
        Trie mTrie;
        bool showCreateOptions;
        bool showTextBox;
        bool editMode;
        int isReversed;
        int textDestionation;
        char textBox[100], requestText[100];
        double mTime, mTimeStep, mTimeStepSlider;
        bool animationPlaying, pendingPause, showRunStepByStep;
        float sliderValue;

        Button *mCreateButton, *mSearchButton, *mInsertButton, *mDeleteButton;
        Button *mClearButton, *mRandomButton, *mCustomButton;
        Button *mRandomValueButton, *mEnterButton;
};

#endif // TrieSTATE_HPP