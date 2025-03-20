#pragma once
#include <memory>
#include <vector>

#include "GUIObject.h"
#include "animation.h"
#include "animationColor.h"
#include "colorPalette.h"
#include "mainLoop.h"
#include "raylib.h"
#include "utility.h"
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
    GraphNode(int label, float posX, float posY)
        : label{label},
          borderColor{PALETTE.borderNormal, PALETTE.borderNormal},
          GUIObject{posX, posY},
          velocity{0.f, 0.f} {};

    void addEdge(std::shared_ptr<GraphNode> dest, int weight);

    void removeEdge(std::shared_ptr<GraphNode> dest);

    void render();

    void highlight(bool isImmediate);

    void deHighlight(bool isImmediate);

    void finishAnimation();

    void update();

    int getLabel();

    bool isCompleted();
    // For force directed drawing

    void setVelocity(Vector2 newVelocity);

    void applyForce(Vector2 force);

    bool isConnected(std::shared_ptr<GraphNode> node);

    AnimationColor &getBorderColor();
};