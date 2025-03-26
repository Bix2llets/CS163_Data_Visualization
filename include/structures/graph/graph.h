#pragma once
#include <vector>

#include "raylib.h"
#include "graph/node.h"
#include "graph/edge.h"

class Graph {
    private:
    // * Data
    // * Render info
    // * Force directed layout
    std::vector<std::shared_ptr<GraphNode>> nodeList;
    std::vector<std::shared_ptr<GraphEdge>> edgeList;
    static const float IDEAL_LENGTH;
    static const float PUSH_FACTOR;
    static const float PULL_FACTOR;
    static const float CENTRIC_FACTOR;
    void handleMouseEvents(); // Handles mouse interactions for dragging nodes

    public:
    void update();

    void render();

    void addNode(int label);

    void addEdge(int node1Label, int node2Label, int weight);

    void removeEdge(int node1Label, int node2Label);

    void removeNode(int nodeLabel);

    bool isAnimationDone();

    void highlightNode(int nodeLabel, bool isImmediate);
    void deHighlightNode(int nodeLabel, bool isImmediate);
    
    void highlightEdge(int node1Label, int node2Label, bool isImmediate);
    void deHighlightEdge(int node1Label, int node2Label, bool isImmediate);

    void makeTransparent(int node1Label, int node2Label, bool isImmediate);
    void makeOpaque(int node1Label, int node2Label, bool isImmediate);

    void applyPushForce();
    void applyPullForce();
    void applyCentricForce();

    std::vector<std::shared_ptr<GraphEdge>> getEdgeList();
    std::vector<std::shared_ptr<GraphNode>> getNodeList();

    void finishAnimation();

    std::shared_ptr<GraphEdge> findEdge(int node1Label, int node2Label);
    std::shared_ptr<GraphNode> findNode(int nodeLabel);
};