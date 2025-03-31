#pragma once
#include <deque>
#include <queue>
#include <set>
#include <unordered_map>
#include "menuPane.h"
#include "graph/graph.h"

namespace GraphScene {
extern Graph graph;

struct ChangeInfo {
    bool isHighlightedBefore;
    bool isHighlightedAfter;
    bool isOpaqueBefore;
    bool isOpaqueAfter;

    bool isImmediate;
};
struct NodeChange {
    int label;
    ChangeInfo info;
};

struct EdgeChange {
    int label1, label2;
    ChangeInfo info;
};
struct Action {
    struct EdgeInfo {
        int node1;
        int node2;
        int weight;
    };
    std::vector<NodeChange> nodeChange;
    std::vector<EdgeChange> edgeChange;
    std::vector<int> nodeAdded;
    std::vector<int> nodeDeleted;
    std::vector<EdgeInfo> edgeAdded;
    std::vector<EdgeInfo> edgeDeleted;
    int highlightedLine = -1;
    std::vector<std::string> const *highlightRef;
};

struct djikstraCmp {
    bool operator()(std::pair<int, int> node1, std::pair<int, int> node2) {
        return node1.second > node2.second;
    }
};
extern std::deque<Action> past;
extern std::deque<Action> future;
extern std::deque<Action> steps;
extern float accumulatedTime;
extern const float TIME_DELAY;
extern int currentHighlighting;

const extern std::vector<std::string> PSEUDO_BLANK;
const extern std::vector<std::string> PSEUDO_MST;
const extern std::vector<std::string> PSEUDO_DIJKSTRA;

extern std::set<int> nodeList;
extern std::set<std::pair<std::pair<int, int>, int>> edgeList;

extern MenuPane addPane;
extern MenuPane deletePane;
extern MenuPane algoPane;
extern MenuPane storagePane;

void init();
void setPanePosition(Vector2 position);

void update();
void render();

void addNode(int nodeLabel);
void addNode(std::shared_ptr<GraphNode> node);

void addEdge(int node1Label, int node2Label, int weight);
void addEdge(std::shared_ptr<GraphNode> node1, std::shared_ptr<GraphNode> node2,
             int weight);

void removeNode(int nodeLabel);
void removeNode(std::shared_ptr<GraphNode> node);

void removeEdge(int node1Label, int node2Label);
void removeEdge(std::shared_ptr<GraphNode> node1,
                std::shared_ptr<GraphNode> node2);

void prevStep();
void nextStep();

int getParent(int label, std::unordered_map<int, int> &parList);
bool join(int label1, int label2, std::unordered_map<int, int> &parList);

void MST();
void dijkstra(int source);

void registerInput();

void addStep(int highlightedLine, std::vector<std::string> const *ref);
// With animation
void addNodeChange(int label, ChangeInfo info);
void addEdgeChange(int label1, int label2, ChangeInfo info);
// No animation
void addNodeAdd(int label);
void addNodeDelete(int label);
void addEdgeAdd(int label1, int label2, int weight);
void addEdgeDelete(int label1, int label2, int weight);

// For getting next info, cannot be used with multiple succession of animaton
ChangeInfo getInfo(std::shared_ptr<GraphNode> node, bool isResultHighlight,
                   bool isResultOpaque, bool isImmediate);
ChangeInfo getInfo(std::shared_ptr<GraphEdge> edge, bool isResultHighlight,
                   bool isResultOpaque, bool isImmediate);

void resetGraphColor();

void backward();
void forward();
}  // namespace GraphScene