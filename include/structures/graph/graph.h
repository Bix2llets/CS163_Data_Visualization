#pragma once
#include <vector>

#include "raylib.h"
#include "node.h"
#include "edge.h"

class Graph {
    std::vector<GraphNode> nodeList;
    std::vector<GraphEdge> edgeList;

    static const Vector2 UPPER_LEFT;
    static const Vector2 LOWER_RIGHT;
};