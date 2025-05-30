#pragma once
#include <memory>
#include <vector>

#include "GUIObject.h"
#include "animation.h"
#include "dynamicColor.h"
#include "colorPalette.h"
#include "raylib.h"
#include "utility.h"
#include "AppInfo.h"
class GraphNode : public GUIObject {
   private:
    struct OutgoingEdge {
        std::shared_ptr<GraphNode> dest;
        int weight;
    };
    int label;
    std::vector<OutgoingEdge> adjacentList;
    // Drawing info
    const static int BORDER_WIDTH;
    DynamicColor borderColor;
    // For force directed
    Vector2 velocity;
    const static float MASS;
    bool isHighlighted;
    bool isOpaque;
    bool dragged; // Track if the node is being dragged
    
    public:
    static Color const *HOVER;
    static ColorSet const *PALETTE;
    const static int RADIUS;
    GraphNode(int label, float posX, float posY)
        : label{label},
          borderColor{&PALETTE->borderNormal, &PALETTE->borderNormal},
          GUIObject{posX, posY},
          velocity{0.f, 0.f},
          isHighlighted{false},
          isOpaque{true},
          dragged{false} {};

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

    void makeOpaque(bool isImmediate);
    void makeTransparent(bool isImmediate);

    bool getOpaque();
    bool getHighlighted();

    void setDragging(bool dragging) { dragged = dragging; }
    bool isDragging() const { return dragged; }
    void setPosition(Vector2 newPosition) { position = newPosition; }
};