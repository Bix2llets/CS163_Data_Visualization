#ifndef AVLSTATE_HPP
#define AVLSTATE_HPP

#include "raylib.h"
#include <cstring>
#include "AVL.hpp"
#include "button.h"
#include "menuPane.h"

class AVLState
{
    static ColorSet const *buttonPalette;
    
    public:
        AVLState();
        void handleInput();
        void update();
        void render();
        void run();
        static void initPanes(Vector2 position); // Initialize panes
        ~AVLState();
        static MenuPane addPane, removePane, algoPane, storagePane; // New panes
    private:
        AVL mAVL;
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

#endif // AVLSTATE_HPP