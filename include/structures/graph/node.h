#pragma once
#include <memory>
#include <vector>

#include "GUIObject.h"
#include "animation.h"
#include "animationColor.h"
#include "colorPalette.h"
#include "raylib.h"
#include "utility.h"
#include "colorPalette.h"

#include "mainLoop.h"
class GraphNode : public GUIObject {
   private:
    struct OutgoingEdge {
        std::shared_ptr<GraphNode> dest;
        int weight;
    };
    int label;
    std::vector<OutgoingEdge> adjacentList;
    // Drawing info
    const static ColorSet PALETTE;
    const static int RADIUS;
    const static int BORDER_WIDTH;
    AnimationColor borderColor;
    // For force directed
    Vector2 velocity;
    const static float MASS;
   public:
   GraphNode(int label, int posX = RADIUS, int posY = RADIUS)
   : label{label},
   borderColor{PALETTE.borderNormal, PALETTE.borderNormal},
   GUIObject{posX, posY} {};
   
   void addEdge(std::shared_ptr<GraphNode> dest, int weight);
   
   void removeEdge(std::shared_ptr<GraphNode> dest);
   
   void render();

    void highlight();

    void deHighlight();

    void finishAnimation();

    void update();

    // For force directed drawing

    void setVelocity(Vector2 newVelocity);

    void applyForce(Vector2 force);
};