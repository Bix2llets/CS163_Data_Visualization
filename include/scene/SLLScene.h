#pragma once
#include "singlyLinkedList.h"
#include "appMenu.h"
#include "mainLoop.h"
#include "utility.h"
#include <deque>
#include <vector>
#include <string> 
namespace SLLScene {
    struct SLLStorage {
        SLL sll;
        int highlightIndex;
        std::vector<std::string> const *highlightRef = nullptr;
    };
    
    namespace AddMenu{

        extern const Vector2 FORM_DIMENSION;
        extern const Vector2 BUTTON_DIMENSION;
        extern const Vector2 BUTTON_DISTANCE;
        extern const Vector2 STARTING_POSITION;
        extern Button addEndButton;
        extern Button addAtButton;
        extern Form locationForm;
        extern Form valueForm;
        extern bool isEnabled;

        void recordInput();
        void render();
    }
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

    extern ColorSet const *NODE_PALETTE;
    void setSpecs(float _stepDelay = 0.5f);

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


}