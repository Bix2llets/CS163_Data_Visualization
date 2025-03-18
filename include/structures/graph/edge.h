#pragma once
#include <memory>

#include "node.h"

class GraphEdge : public GUIObject {
   private:
    std::shared_ptr<GraphNode> node1;
    std::shared_ptr<GraphNode> node2;
    int weight;

    // Drawing info
    const static int THICKNESS;
    AnimationColor color;
    const static Color NORMAL_COLOR;
    const static Color HIGHLIGHT_COLOR;
    const static Color TEXT_COLOR;

   public:
    GraphEdge(std::shared_ptr<GraphNode> node1,
              std::shared_ptr<GraphNode> node2, int weight)
        : node1{node1},
          node2{node2},
          weight{weight},
          color{NORMAL_COLOR, NORMAL_COLOR},
          GUIObject(Vector2Scale(
              Vector2Add(node1->getPosition(), node2->getPosition()), 0.5f)) {};

    void update();
    void render();

    void highlight();
    void deHighlight();
    void makeTransparent();
    void makeOpaque();

};
