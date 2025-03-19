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
    public:
    void update();

    void render();

    void addNode(int label);


    void addEdge(int node1Label, int node2Label, int weight);

    void removeEdge(int node1Label, int node2Label);

    void removeNode(int nodeLabel);

    bool isAnimationDone();

    void highlightNode(int nodeLabel);
    void deHighlightNode(int nodeLabel);
    
    void highlightEdge(int node1Label, int node2Label);
    void deHighlightEdge(int node1Label, int node2Label);

    void applyPushForce();
    void applyPullForce();
    void applyCentricForce();

    std::vector<std::shared_ptr<GraphEdge>> getEdgeList();
};