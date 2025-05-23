#ifndef MENU_HPP
#define MENU_HPP

#include "button.h"
#include "mainLoop.h"
#include "CodePane.h"
// #include "insertBox.hpp"
// #include "edgeInsertBox.hpp"
#include "textureButton.h"
#include "menuPane.h"
#include <Utility.h>
#include "TrieScene.h"
#include "AVLScene.h"
#include "hashScene.h"
#include "graphScene.h"
#include "SLLScene.h"
namespace MenuTable {
    enum Type {
        CREATE, // show random, clear, and import button
        EdgeInsert, // u, v, w - edgeInsertBox
        NumInsert, // other insertBox - insert text, delete text, search text, insert num, delete num, search num
        TextInsert,
        None // no input
    };
    extern float minValue, maxValue, sliderValue;
    extern TextureBox backwardButton, forwardButton, prevButton, nextButton, playButton, pauseButton; 
    extern Vector2 optionPosition;
    extern Vector2 optionDimension;
    extern Vector2 optionDistance;

    extern Vector2 sliderBarPos, sliderBarDimension;
    extern Button showMenu;
    extern bool showMenuFlag, *isPlaying;
    extern MenuPane basePane;
    extern MenuPane* addPane;
    extern MenuPane* deletePane;
    extern MenuPane* algoPane;
    extern MenuPane* storagePane;
    void Constructor(Vector2 _optionPosition, Vector2 _optionDimension, Vector2 _sliderBarPos, Vector2 _sliderBarDimension);
    void init();
    void render();
    void handleInput();

    void continueAnimation();
    void pauseAnimation();
};

#endif // MENU_HPP