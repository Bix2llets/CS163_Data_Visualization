#include <cmath>
#pragma once
#include "animation.h"
#include "animationColor.h"
#include "arrow.h"
#include "colorPalette.h"
#include "raylib.h"
#include "raymath.h"
#include "utility.h"

Vector2 getNextNodePosition(Vector2 currentPosition, int horizontalDistance, int verticalDistance, int nodePerRow, int currentIndex);
class Node : public Animation {
    // ! Support up to 4 digits number
    std::string data;
    const ColorSet PALETTE;
    int radius;
    float animationRate;
    friend class SLL;
    public:
    AnimationColor borderColor;
    AnimationColor edgeColor;
    Node* nextNode;
    Node(std::string data, float x, float y, int radius = 50,
         ColorSet palette = COLOR_SET_1);
    Node(int data, float x, float y, int radius = 50,
         ColorSet palette = COLOR_SET_1);

    // * Constructor done

    void render();
    void update();

    void updateAnimation();
    bool isFinished();

    void finishAnimation();
};
