#pragma once
#include <deque>

#include "SLLNode.h"
class SLL {
     public:
    const static ColorSet NODE_PALETTE;
    const static int NODE_RADIUS;
    const static int DISTANCE_HORIZONTAL;
    const static int DISTANCE_VERTICAL;

    int nodePerRow;
    Rectangle drawArea;
    int nodeCount;
    float animationRate;

    Node* root;

    SLL(Rectangle area = {100, 100, 1400, 400}, float animationRate = 1.0f);
    SLL(const SLL &sll);
    // ~SLL();
    void update();
    void setAnimationRate(float rate);
    
    void addEnd(std::string data);
    void addAt(std::string data, int place);
    void render();
    void removeEnd();
    void removeAt(int place);

    void shiftForward(int place);
    void shiftBackward(int place);

    bool isFinished();
    void finishAnimation();

    void moveAt(int place);
    void moveEnd();
    
    int locate(std::string val);
    void highlightTo(int place);
    void deHighlight();
    SLL clone();

    SLL operator=(const SLL &source);

    void freeMemory();

};  // namespace SLL