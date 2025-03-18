#pragma once
#include "singlyLinkedList.h"
#include "appMenu.h"
#include "mainLoop.h"
#include <deque>
#include <vector>
#include <string> 
namespace SLLScene {
    struct SLLStorage {
        SLL sll;
        int highlightIndex;
    };
    
    extern float stepDelay;
    extern float timeLeft;
    extern SLL sll;
    extern int highlightedRow;

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

    extern const ColorSet NODE_PALETTE;
    void setSpecs(float _stepDelay = 0.5f);

    void addEnd(std::string data);

    void addAt(std::string data, int place);
    
    void removeEnd();

    void removeAt(int place);

    void update();

    void addStep(int highlightIndex);
    
    void render();

    void find(std::string val);

    void clearScene();

    void recordInput();

    void prevStep();

    void nextStep();

    void init();
}