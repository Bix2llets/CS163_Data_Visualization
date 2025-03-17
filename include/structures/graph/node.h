#pragma once
#include <memory>
#include <vector>

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
    static int radius;
    std::vector<OutgoingEdge> adjacentNodes;
    AnimationColor borderColor;
   public:
   void render();
   
   void addEdge(std::shared_ptr<GraphNode> dest, int weight);
   
   void removeEdge(std::shared_ptr<GraphNode> dest);
   
   void setUpdateRate(float rate);
   
   void highlight();
   
   void deHighlight();

   GraphNode(int label) : label{label}, borderColor{PALETTE.borderNormal, PALETTE.borderNormal, updateRate}, Animation{radius, radius, updateRate} {};
};