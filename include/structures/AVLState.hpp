#ifndef AVLSTATE_HPP
#define AVLSTATE_HPP

#include "raylib.h"
#include <cstring>
#include "AVL.hpp"

class AVLState
{
    public:
        AVLState();
        void handleInput();
        void update();
        void render();
        void run();
        ~AVLState();
    private:
        AVL mAVL;
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

#endif // AVLSTATE_HPP