#ifndef TRIESTATE_HPP
#define TRIESTATE_HPP

#include "raylib.h"
#include <cstring>
#include "Trie.hpp"

class TrieState
{
    public:
        TrieState();
        void handleInput();
        void update();
        void render();
        void run();
        ~TrieState();
    private:
        Trie mTrie;
        bool showOptions;
        bool showCreateOptions;
        bool showTextBox;
        bool editMode;
        int isReversed;
        int textDestionation;
        char textBox[100], requestText[100];
        double mTime, mTimeStep;
        bool animationPlaying, pendingPause, showRunStepByStep, forward, backward;
        float sliderValue;
};

#endif // TRIESTATE_HPP