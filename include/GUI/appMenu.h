#pragma once
#include "button.h"
#include "textbox.h"
#include "form.h"
#include "colorPalette.h"
#include <vector>
enum class SceneList {
    MAIN_MENU,
    LINKED_LIST,
    TRIE,
    GRAPH,
    HASH
};
namespace AppMenu {
    extern Vector2 codeBlockPosition;
    extern Vector2 codeLineSize;
    extern ColorSet codeBlockColor; 
    
    extern Button addByValueButton;
    extern Button addAtIndexButton;
    extern Button addButton;

    extern Button removeByValueButton;
    extern Button removeAtIndexButton;
    extern Button removeButton;

    extern Form locationBox;
    extern Form valueBox;

    extern std::vector<GUIObject*> renderList;
    extern std::vector<TextBox> codeList; 

    void init();

    void render();

    void loadCode(const std::vector<std::string> &strVect);
}