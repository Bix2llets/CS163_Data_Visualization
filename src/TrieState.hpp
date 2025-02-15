#ifndef TRIESTATE_HPP
#define TRIESTATE_HPP

#include "raylib.h"
#include "..\..\..\src\Trie.hpp"

class TrieState 
{
    public:
        TrieState();
        void handleInput();
        void update();
        void render();
    private:
        Trie trie;
        bool showOptions;
        bool showCreateOptions;
        bool showTextBox;
        char textBox[256] = "";
        int textDestionation = 0;
        bool editMode;
};

#endif // TRIESTATE_HPP