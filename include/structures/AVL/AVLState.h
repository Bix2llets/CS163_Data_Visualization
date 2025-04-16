#ifndef AVLSTATE_HPP
#define AVLSTATE_HPP

#include "raylib.h"
#include <cstring>
#include "AVL.h"
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
        static void setAnimationSpeed(float factor);
    private:
        AVL mAVL;
        bool showCreateOptions;
        bool showTextBox;
        int isReversed;
        static double mTimeStep;
        double mTime, mTimeStepSlider;
        bool animationPlaying, pendingPause;
        float sliderValue;

        // Button *mCreateButton, *mSearchButton, *mInsertButton, *mDeleteButton;
        // Button *mClearButton, *mRandomButton, *mCustomButton;
        // Button *mRandomValueButton, *mEnterButton;

};

#endif // AVLSTATE_HPP