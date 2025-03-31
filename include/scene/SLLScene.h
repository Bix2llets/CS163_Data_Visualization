#pragma once
#include "singlyLinkedList.h"
#include "appMenu.h"
#include "mainLoop.h"
#include "utility.h"
#include "menuPane.h"
#include "mLib/tinyfiledialogs.h"
#include "menu.hpp"
#include <deque>
#include <vector>
#include <string>
#include <fstream> 
namespace SLLScene {
    struct SLLStorage {
        SLL sll;
        int highlightIndex;
        std::vector<std::string> const *highlightRef = nullptr;
    };
    
    
    extern float stepDelay;
    extern float timeLeft;
    extern SLL sll;
    extern int highlightedRow;
    extern const Vector2 STARTING_PANE_POSITION;
    extern MenuPane addPane;
    extern MenuPane deletePane;
    extern MenuPane algoPane;
    extern MenuPane miscPane;
    extern const Rectangle CANVAS;
    extern float animationRate;
    extern std::deque<SLLStorage> steps;
    extern std::deque<SLLStorage> past;
    extern std::deque<SLLStorage> future;
    // * For pseudo code rendered in code panel
    extern const std::vector<std::string> PSEUDO_INSERT;
    extern const std::vector<std::string> PSEUDO_DELETE;
    extern const std::vector<std::string> PSEUDO_SEARCH;
    // --------------------------

    extern ColorSet const *NODE_PALETTE;
    void setDelay(float _stepDelay = 0.5f);

    void addEnd(std::string data);

    void addAt(std::string data, int place);
    
    void removeEnd();

    void removeAt(int place);

    void update();

    void addStep(int highlightIndex, std::vector<std::string> const *ref);
    
    void render();

    void find(std::string val);

    void clearScene();

    void recordInput();

    void prevStep();
    void backward();
    
    void nextStep();
    void forward();

    void init();

    void correctAnimation();

    void setPanePosition(Vector2 newPosition);


}