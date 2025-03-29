#ifndef MENU_HPP
#define MENU_HPP

#include "button.h"

#include "appMenu.h"
#include "insertBox.hpp"
#include "edgeInsertBox.hpp"
#include "textureButton.hpp"
#include <mLib/Utility.hpp>

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
    extern Vector2 sliderBarPos, sliderBarDimension;
    extern Button showMenu;
    extern Button clearButton, importButton, randomButton;
    extern InsertBox insertBox;
    extern edgeInsertBox edgeBox;
    extern std::string requestText, requestNum;
    extern std::vector<std::string> requestEdge; // u, v, w
    extern bool showMenuFlag, requestClear, requestImport, requestRandom, inAnimationProcess, isPlaying;
    extern std::vector<std::pair<Button *, Type>> GUIObjects;
    extern int MaxSizeNum, MaxSizeText, MaxSizeWeight;
    void Constructor(Vector2 _optionPosition, Vector2 _optionDimension, Vector2 _sliderBarPos, Vector2 _sliderBarDimension);
    void init();
    void render();
    void handleInput();
    void CLEAR();
    void pack(Button *obj, Type type);
};

#endif // MENU_HPP