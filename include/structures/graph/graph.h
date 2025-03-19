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
    void addNode(std::shared_ptr<GraphNode> node);

    void addNode(int label);

    void addEdge(std::shared_ptr<GraphNode> node1, std::shared_ptr<GraphNode> node2, int weight);

    void addEdge(int node1Label, int node2Label, int weight);

    bool isAnimationDone();

    void highlightNode(std::shared_ptr<GraphNode> node);
    void deHighlightNode(std::shared_ptr<GraphNode> node);
    
    void highlightEdge(std::shared_ptr<GraphEdge> edge);
    void deHighlightEdge(std::shared_ptr<GraphEdge> edge);

    void applyPushForce();
    void applyPullForce();
    void applyCentricForce();

    std::vector<std::shared_ptr<GraphEdge>> getEdgeList();
};