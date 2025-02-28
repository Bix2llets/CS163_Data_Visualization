#pragma once
#include "singlyLinkedList.h"
#include <deque>
namespace SLLScene {
    extern float stepDelay;
    extern float timeLeft;

    extern const Rectangle CANVAS;
    extern float animationRate;
    extern SLL sll;

    void addEnd();
    void addAt(int place);
    
    void deleteEnd();
    void deleteAt(int place);

    void update();
    
}