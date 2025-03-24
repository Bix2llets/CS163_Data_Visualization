#ifndef hashSTATE_HPP
#define hashSTATE_HPP

#include "raylib.h"
#include <cstring>
#include "hash.hpp"
#include "button.h"

class hashState
{
    ColorSet buttonPalette = {
        Color{186, 180, 163, 255}, Color{186, 180, 163, 255},
        Color{51, 49, 45, 255},    Color{42, 114, 47, 255},
        Color{229, 189, 80, 255},  Color{229, 189, 80, 255},
    };
    
    public:
        hashState();
        void handleInput();
        void update();
        void render();
        void run();
        ~hashState();
    private:
        hash mhash;
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

#endif // hashSTATE_HPP
