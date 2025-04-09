#include <cmath>
#pragma once
#include "animation.h"
#include "DynamicColor.h"
#include "arrow.h"
#include "colorPalette.h"
#include "raylib.h"
#include "raymath.h"
#include "utility.h"

Vector2 getNextNodePosition(Vector2 currentPosition, int horizontalDistance, int verticalDistance, int nodePerRow, int currentIndex);
class Node : public Animation {
    // ! Support up to 4 digits number
    std::string data;
    int radius;
    float animationRate;
    friend class SLL;
    public:
    static ColorSet const *PALETTE;
    DynamicColor borderColor;
    DynamicColor edgeColor;
    Node* nextNode;
    Node(std::string data, float x, float y, int radius = 50);
    Node(int data, float x, float y, int radius = 50);

    // * Constructor done

    void render();
    void update();

    void updateAnimation();
    bool isFinished();

    void finishAnimation();
};
