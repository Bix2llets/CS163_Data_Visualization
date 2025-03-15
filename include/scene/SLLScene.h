#pragma once
#include "singlyLinkedList.h"
#include <deque>
#include <vector>
#include <string> 
namespace SLLScene {
    extern float stepDelay;
    extern float timeLeft;

    extern const Rectangle CANVAS;
    extern float animationRate;
    extern SLL sll;
    extern std::deque<SLL> steps;

    extern std::vector<std::string> pseudoCodeList; 
    void setSpecs(float _stepDelay = 0.5f, float _animationRate = 1.f);

    void addEnd(std::string data);

    void addAt(std::string data, int place);
    
    void removeEnd();

    void removeAt(int place);

    void update();

    void addStep();
    
    void render();

    void find(std::string val);

    void mainLoop();
}