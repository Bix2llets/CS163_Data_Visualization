#pragma once
#include <memory>
#include <vector>

#include "raylib.h"
#include "GUIObject.h"
#include "animation.h"
#include "animationColor.h"
#include "colorPalette.h"
class GraphNode : public Animation {
   private:
    struct OutgoingEdge {
        std::shared_ptr<GraphNode> dest;
        int weight;
    };
    int label;
    const static ColorSet PALETTE;
    static float updateRate;
    const static int RADIUS;
    const static int BORDER_WIDTH;
    std::vector<OutgoingEdge> adjacentNodes;
    AnimationColor borderColor;
   public:
   void render();
   
   void addEdge(std::shared_ptr<GraphNode> dest, int weight);
   
   void removeEdge(std::shared_ptr<GraphNode> dest);
   
   void highlight();
   
   void deHighlight();

   GraphNode(int label, int posX = RADIUS, int posY = RADIUS) : label{label}, borderColor{PALETTE.borderNormal, PALETTE.borderNormal, updateRate}, Animation{posX, posY} {};
};