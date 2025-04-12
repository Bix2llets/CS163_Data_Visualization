#pragma once
#include <deque>

#include "Appinfo.h"
#include "SLLNode.h"
class SLL {
     public:
    static ColorSet const *NODE_PALETTE;
    const static int NODE_RADIUS;
    const static int DISTANCE_HORIZONTAL;
    const static int DISTANCE_VERTICAL;

    int nodePerRow;
    Rectangle drawArea;
    int nodeCount;

    Node* root;

    SLL(Rectangle area = {AppInfo::UPPER_LEFT.x, AppInfo::UPPER_LEFT.y, AppInfo::LOWER_RIGHT.x - AppInfo::UPPER_LEFT.x, AppInfo::LOWER_RIGHT.y - AppInfo::UPPER_LEFT.y});
    SLL(const SLL &sll);
    // ~SLL();
    void update();
    
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
    std::string getSaveData();

};  // namespace SLL