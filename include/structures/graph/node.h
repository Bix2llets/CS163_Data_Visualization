#pragma once
#include <memory>
#include <vector>

#include "GUIObject.h"
#include "animation.h"
#include "animationColor.h"
#include "colorPalette.h"
#include "raylib.h"
#include "utility.h"
class GraphNode : public GUIObject {
   private:
    struct OutgoingEdge {
        std::shared_ptr<GraphNode> dest;
        int weight;
    };
    int label;
    const static ColorSet PALETTE;
    const static int RADIUS;
    const static int BORDER_WIDTH;
    std::vector<OutgoingEdge> adjacentList;
    AnimationColor borderColor;

   public:
    void render();

    void addEdge(std::shared_ptr<GraphNode> dest, int weight);

    void removeEdge(std::shared_ptr<GraphNode> dest);

    void highlight();

    void deHighlight();

    void finishAnimation();
    void update();
    GraphNode(int label, int posX = RADIUS, int posY = RADIUS)
        : label{label},
          borderColor{PALETTE.borderNormal, PALETTE.borderNormal},
          GUIObject{posX, posY} {};
};