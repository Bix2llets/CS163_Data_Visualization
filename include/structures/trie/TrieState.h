#ifndef TrieSTATE_HPP
#define TrieSTATE_HPP

#include "raylib.h"
#include <cstring>
#include "Trie.h"
#include "button.h"
#include "menuPane.h"
class TrieState
{
    ColorSet const *buttonPalette = &buttonColorSet;
    
    public:
        TrieState();
        void handleInput();
        void update();
        void render();
        void run();
        ~TrieState();
        
        static void initPanes(Vector2 position);
        static MenuPane addPane, removePane, algoPane, storagePane;

        static void setAnimationSpeed(float factor);
    private:
        Trie mTrie;
        bool showCreateOptions;
        bool showTextBox;
        bool editMode;
        int isReversed;
        int textDestionation;
        char textBox[100], requestText[100];
        double static mTimeStep;
        double mTime, mTimeStepSlider;
        bool animationPlaying, pendingPause, showRunStepByStep;
        float sliderValue;

        Button *mCreateButton, *mSearchButton, *mInsertButton, *mDeleteButton;
        Button *mClearButton, *mRandomButton, *mCustomButton;
        Button *mRandomValueButton, *mEnterButton;

};

#endif // TrieSTATE_HPP