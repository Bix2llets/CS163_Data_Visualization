#ifndef hashState_HPP
#define hashState_HPP

#include "raylib.h"
#include <cstring>
#include "hash.hpp"

class hashState
{
    public:
        hashState();
        void handleInput();
        void update();
        void render();
        void run();
        ~hashState();
        void printTable();
    private:
        hash mhash;
        bool showOptions;
        bool showCreateOptions;
        bool showTextBox;
        bool editMode;
        int isReversed;
        int textDestionation;
        char textBox[100], requestText[100];
        double mTime, mTimeStep, mTimeStepSlider;
        bool animationPlaying, pendingPause, showRunStepByStep, forward, backward;
        float sliderValue;
};

#endif // hashState_HPP