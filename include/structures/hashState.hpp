#ifndef hashSTATE_HPP
#define hashSTATE_HPP

#include "raylib.h"
#include <cstring>
#include "hash.hpp"
#include "button.h"
#include "menuPane.h"

class HashState
{
    ColorSet const *buttonPalette = &buttonColorSet;
    
    public:
        HashState();
        void handleInput();
        void update();
        void render();
        void run();
        static void initPanes(Vector2 position); // Changed to static
        ~HashState();

        static void setAnimationSpeed(float factor);

        static MenuPane addPane;
        static MenuPane removePane;
        static MenuPane algoPane;
        static MenuPane storagePane;
    private:
        Hash mhash;
        bool showCreateOptions;
        bool showTextBox;
        bool editMode;
        int isReversed;
        int textDestionation;
        char textBox[100], requestText[100];
        static double mTimeStep;
        double mTime, mTimeStepSlider;
        bool animationPlaying, pendingPause, showRunStepByStep;
        float sliderValue;

        // Menu panes

        Button *mCreateButton, *mSearchButton, *mInsertButton, *mDeleteButton;
        Button *mClearButton, *mRandomButton, *mCustomButton;
        Button *mRandomValueButton, *mEnterButton;
};

#endif // hashSTATE_HPP
