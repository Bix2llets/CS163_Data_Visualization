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
    private:
        AVL mAVL;
        bool showOptions;
        bool showCreateOptions;
        bool showTextBox;
        bool editMode;
        int textDestionation;
        char textBox[100], requestText[100];
        float mTime;
};

#endif // AVLSTATE_HPP