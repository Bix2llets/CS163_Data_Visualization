#pragma once
#include "button.h"
#include "raylib.h"
namespace WelcomeMenu {
extern const int BANNER_WIDTH;
extern const int BANNER_HEIGHT;
extern const int BANNER_X;
extern const int BANNER_Y;
extern const int LEFT_MARGIN;
extern const int UPPER_MARGIN;
extern const int BUTTON_DISTANCE;
extern const int FONT_SIZE;
extern const Color BUTTON_TEXT_COLOR;
extern const Color BUTTON_BACKGROUND_COLOR;
extern const Color BUTTON_HIGHLIGHT_COLOR;
void render();
bool isTriePressed();
bool isLinkedListPressed();
bool isGraphPressed();
bool isHashTablePressed();
bool isAVLTreePressed();
extern Button trie;
extern Button linkedList;
extern Button graph;
extern Button hashTable;
extern Button AVLTree;

}  // namespace WelcomeMenu