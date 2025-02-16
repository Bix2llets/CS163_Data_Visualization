#ifndef TRIESTATE_HPP
#define TRIESTATE_HPP

#include "raylib.h"
#include <cstring>
#include "..\..\..\src\Trie.hpp"

class TrieState
{
    public:
        TrieState();
        void handleInput();
        void update();
        void render();
    private:
        Trie mTrie;
        bool showOptions;
        bool showCreateOptions;
        bool showTextBox;
        bool editMode;
        int textDestionation;
        char textBox[100], requestText[100];
};

#endif // TRIESTATE_HPP