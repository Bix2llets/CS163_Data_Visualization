#include "graphScene.h"

#include <sstream>
#include <unordered_map>
namespace GraphScene {
Graph graph;
std::deque<Action> past;
std::deque<Action> future;
std::deque<Action> steps;
float timeLeft = 0.0f;
const float TIME_DELAY = 0.1f;  // Adjust the delay as needed
int currentHighlighting = -1;

std::set<int> nodeList;
std::set<std::pair<std::pair<int, int>, int>> edgeList;
const std::vector<std::string> PSEUDO_BLANK;
const std::vector<std::string> PSEUDO_MST = {
    "Remove all edges", "Choose edge of minimum weight", "Join the vertices"};
const std::vector<std::string> PSEUDO_DIJKSTRA = {
    "Set the distance to source to 0", "Set the distance to others to infinity",
    "Choose vertex with minimum distance", "Examine the adjacent vextices"};
void update() {
    graph.update();
    if (!graph.isAnimationDone()) return;
    if (steps.size() == 0) timeLeft = 0;
    timeLeft -= GetFrameTime();
    if (timeLeft <= 0 && steps.size()) {
        Action nextAction = steps.front();
        steps.pop_front();
        past.push_back(nextAction);
        timeLeft = TIME_DELAY;
        currentHighlighting = nextAction.highlightedLine;

        for (NodeChange nodeChange : nextAction.nodeChange) {
            auto node = graph.findNode(nodeChange.label);
            bool isImmediate = nodeChange.info.isImmediate;

            if (nodeChange.info.isHighlightedAfter) {
                node->highlight(isImmediate);
            } else
                node->deHighlight(isImmediate);

            if (nodeChange.info.isOpaqueAfter) {
                node->makeOpaque(isImmediate);
            } else
                node->makeTransparent(isImmediate);
        }

        for (EdgeChange edgeChange : nextAction.edgeChange) {
            auto edge = graph.findEdge(edgeChange.label1, edgeChange.label2);
            bool isImmediate = edgeChange.info.isImmediate;
            ChangeInfo info = edgeChange.info;

            if (info.isHighlightedAfter) {
                edge->highlight(isImmediate);
            } else
                edge->deHighlight(isImmediate);

            if (info.isOpaqueAfter) {
                edge->makeOpaque(isImmediate);
            } else
                edge->makeTransparent(isImmediate);
        }

        // * For addition and deletion

        for (int label : nextAction.nodeAdded) graph.addNode(label);
        for (int label : nextAction.nodeDeleted) graph.removeNode(label);
        for (auto [label1, label2, weight] : nextAction.edgeAdded)
            graph.addEdge(label1, label2, weight);
        for (auto [label1, label2, weight] : nextAction.edgeDeleted)
            graph.removeEdge(label1, label2);
    }
}

void render() { graph.render(); }

void addNode(int nodeLabel) {
    if (nodeList.find(nodeLabel) != nodeList.end()) return;
    addStep(-1);
    resetGraphColor();
    addNodeAdd(nodeLabel);
}

void addNode(std::shared_ptr<GraphNode> node) { addNode(node->getLabel()); }

void addEdge(int node1Label, int node2Label, int weight) {
    if (edgeList.find({{node1Label, node1Label}, weight}) != edgeList.end()) return;
    addStep(-1);
    resetGraphColor();
    addEdgeAdd(node1Label, node2Label, weight);
}

void addEdge(std::shared_ptr<GraphNode> node1, std::shared_ptr<GraphNode> node2,
             int weight) {
    addEdge(node1->getLabel(), node2->getLabel(), weight);
}

void removeNode(int nodeLabel) {
    if (nodeList.find(nodeLabel) == nodeList.end()) return;
    addStep(-1);
    resetGraphColor();
    addNodeDelete(nodeLabel);
    std::vector<std::pair<std::pair<int, int>, int>> deleteList;
    for (auto edge : edgeList) {
        if (edge.first.first == nodeLabel ||
            edge.first.second == nodeLabel)
            deleteList.push_back(edge);
    }

    for (auto edge: deleteList)
        addEdgeDelete(edge.first.first, edge.first.second, edge.second);
}

void removeNode(std::shared_ptr<GraphNode> node) {
    removeNode(node->getLabel());
}

void removeEdge(int node1Label, int node2Label) {
    if (node1Label > node2Label) std::swap(node1Label, node2Label);
    int weight = -1;
    for (auto x: edgeList) {
        if (x.first.first == node1Label && x.first.second == node2Label)
            weight = x.second;
    }
    if (edgeList.find({{node1Label, node2Label}, weight}) == edgeList.end()) return;
    addStep(-1);
    resetGraphColor();
    addEdgeDelete(node1Label, node2Label, weight);
}

void removeEdge(std::shared_ptr<GraphNode> node1,
                std::shared_ptr<GraphNode> node2) {
    
    removeEdge(node1->getLabel(), node2->getLabel());
}

void prevStep() {
    if (past.empty()) return;
    graph.finishAnimation();
    while (steps.size()) {
        future.push_front(steps.back());
        steps.pop_back();
    }
    Action lastAction = past.back();
    past.pop_back();
    future.push_front(lastAction);

    currentHighlighting = lastAction.highlightedLine;
    for (auto [label1, label2, weight] : lastAction.edgeAdded)
        graph.removeEdge(label1, label2);
    for (auto [label1, label2, weight] : lastAction.edgeDeleted)
        graph.addEdge(label1, label2, weight);
    for (int label : lastAction.nodeAdded) graph.removeNode(label);
    for (int label : lastAction.nodeDeleted) graph.addNode(label);

    for (NodeChange nodeChange : lastAction.nodeChange) {
        auto node = graph.findNode(nodeChange.label);
        bool isImmediate = nodeChange.info.isImmediate;
        ChangeInfo info = nodeChange.info;
        if (info.isHighlightedBefore)
            node->highlight(isImmediate);
        else
            node->deHighlight(isImmediate);
        if (info.isOpaqueBefore)
            node->makeOpaque(isImmediate);
        else
            node->makeTransparent(isImmediate);
    }

    for (EdgeChange edgeChange : lastAction.edgeChange) {
        auto edge = graph.findEdge(edgeChange.label1, edgeChange.label2);
        bool isImmediate = edgeChange.info.isImmediate;
        ChangeInfo info = edgeChange.info;
        if (info.isHighlightedBefore)
            edge->highlight(isImmediate);
        else
            edge->deHighlight(isImmediate);
        if (info.isOpaqueBefore)
            edge->makeOpaque(isImmediate);
        else
            edge->makeTransparent(isImmediate);
    }
}

void nextStep() {
    if (steps.size()) {
        graph.finishAnimation();
        timeLeft = 0;
        return;
    }
    if (future.empty()) return;
    graph.finishAnimation();
    timeLeft = 0;
    Action nextAction = future.front();
    future.pop_front();
    steps.push_back(nextAction);
}

void registerInput() {
    if (AppMenu::buttonPanel[0][0].isPressed()) {
        auto result = AppMenu::valueBox.getValue();
        if (result.first == false) return;

        AppMenu::loadCode(PSEUDO_BLANK);
        addNode(result.second);
    }

    if (AppMenu::buttonPanel[1][0].isPressed()) {
        auto result = AppMenu::valueBox.getValue();
        if (result.first == false) return;

        AppMenu::loadCode(PSEUDO_BLANK);
        removeNode(result.second);
    }

    if (AppMenu::buttonPanel[0][1].isPressed()) {
        auto result = AppMenu::valueBox.getText();
        std::string node1Str, node2Str, weightStr;
        std::stringstream ss;
        ss << result;
        ss >> node1Str >> node2Str >> weightStr;
        if (ss.rdbuf()->in_avail() != 0) return;
        if (!isStrNum(node1Str)) return;
        if (!isStrNum(node2Str)) return;
        if (!isStrNum(weightStr)) return;
        AppMenu::loadCode(PSEUDO_BLANK);
        int node1lLabel = std::stoi(node1Str);
        int node2lLabel = std::stoi(node2Str);
        int weightLabel = std::stoi(weightStr);
        addEdge(node1lLabel, node2lLabel, weightLabel);
    }

    if (AppMenu::buttonPanel[1][1].isPressed()) {
        auto result = AppMenu::valueBox.getText();
        std::string node1Str, node2Str;
        std::stringstream ss;
        ss << result;
        ss >> node1Str >> node2Str;
        if (ss.rdbuf()->in_avail() != 0) return;
        if (!isStrNum(node1Str)) return;
        if (!isStrNum(node2Str)) return;
        AppMenu::loadCode(PSEUDO_BLANK);
        int node1Label = std::stoi(node1Str);
        int node2Label = std::stoi(node2Str);
        removeEdge(node1Label, node2Label);
    }

    if (AppMenu::buttonPanel[2][0].isPressed()) {
        AppMenu::loadCode(PSEUDO_MST);
        MST();
    }
    if (AppMenu::buttonPanel[2][1].isPressed()) {
        auto result = AppMenu::valueBox.getText();
        std::stringstream ss;
        std::string node1Text;
        ss << result;
        ss >> node1Text;
        if (ss.rdbuf()->in_avail() != 0) return;
        if (!isStrNum(node1Text)) return;
        AppMenu::loadCode(PSEUDO_DIJKSTRA);
        int node1Label = std::stoi(node1Text);
        dijkstra(node1Label);
    }
    if (AppMenu::undoButton.isPressed()) {
        prevStep();
    }

    else if (AppMenu::redoButton.isPressed()) {
        nextStep();
    }
}

int getParent(int label, std::unordered_map<int, int> &parList) {
    if (parList[label] < 0) return label;
    return label = getParent(parList[label], parList);
}
bool join(int label1, int label2, std::unordered_map<int, int> &parList) {
    label1 = getParent(label1, parList);
    label2 = getParent(label2, parList);
    if (label1 == label2) return false;
    if (parList[label1] > parList[label2]) std::swap(label1, label2);
    parList[label1] += parList[label2];
    parList[label2] = label1;

    return true;
}
void MST() {
    addStep(-1);
    resetGraphColor();
    std::vector<std::shared_ptr<GraphEdge>> edgeList = graph.getEdgeList();
    std::vector<std::shared_ptr<GraphNode>> nodeList = graph.getNodeList();
    sort(edgeList.begin(), edgeList.end(),
         [](std::shared_ptr<GraphEdge> a, std::shared_ptr<GraphEdge> b) {
             return a->getWeight() < b->getWeight();
         });

    std::unordered_map<int, int> parList;
    // * Init DSU
    for (std::shared_ptr<GraphNode> node : nodeList)
        parList[node->getLabel()] = -1;

    std::vector<std::shared_ptr<GraphEdge>> restoreList;
    addStep(0);
    for (auto edge : graph.getEdgeList()) {
        ChangeInfo info = getInfo(edge, 0, 0, 0);

        addEdgeChange(edge->node1->getLabel(), edge->node2->getLabel(), info);
    }

    for (std::shared_ptr<GraphEdge> edge : edgeList) {
        int label1 = edge->node1->getLabel();
        int label2 = edge->node2->getLabel();
        int prevState1 = parList[label1];
        int prevState2 = parList[label2];
        if (join(label1, label2, parList)) {
            {
                addStep(1);
                addEdgeChange(label1, label2, ChangeInfo{0, 1, 0, 1, 0});
                if (1 || prevState1 == -1) {
                    addStep(2);
                    addNodeChange(label1, getInfo(edge->node1, 1, 1, 0));
                }
                if (1 || prevState2 == -1) {
                    addStep(2);
                    addNodeChange(label2, getInfo(edge->node2, 1, 1, 0));
                }
            }
        } else {
            restoreList.push_back(edge);
        }
    }
    addStep(-1);
    for (auto edge : restoreList) {
        addEdgeChange(edge->node1->getLabel(), edge->node2->getLabel(),
                      {0, 0, 0, 1, 0});
    }
}

void dijkstra(int source) {
    // * Build the adjacency list (undirected) and init the minimumDistance to
    // nodes
    if (nodeList.find(source) == nodeList.end()) return;
    addStep(-1);
    resetGraphColor();
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjList;
    std::unordered_map<int, int> minimumDistance;
    const int INF = int(1e9 + 7);
    for (auto node : graph.getNodeList()) {
        adjList[node->getLabel()].resize(0);

        if (node->getLabel() != source) {
            addStep(1);
            minimumDistance[node->getLabel()] = INF;
            addNodeChange(node->getLabel(), getInfo(node, 1, 1, 0));
        }
    }
    addStep(0);
    minimumDistance[source] = 0;
    addNodeChange(source, {0, 1, 1, 1, 0});

    addStep(-1);
    for (auto node : graph.getNodeList())
        addNodeChange(node->getLabel(), {1, 0, 1, 1, 0});
    for (auto edge : graph.getEdgeList()) {
        int label1 = edge->node1->getLabel();
        int label2 = edge->node2->getLabel();
        int weight = edge->getWeight();
        adjList[label1].push_back({label2, weight});
        adjList[label2].push_back({label1, weight});
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        djikstraCmp>
        pq;

    pq.push({source, 0});
    // addStep();
    // addNodeChange(source, {0, 1, 1, 1, 0});
    while (pq.size()) {
        std::pair<int, int> curr = pq.top();
        pq.pop();
        addStep(2);
        addNodeChange(curr.first, getInfo(graph.findNode(curr.first), 1, 1, 0));
        // * Traverse the adjacency list
        for (std::pair<int, int> edge : adjList[curr.first]) {
            int nextWeight = curr.second + edge.second;
            if (nextWeight < minimumDistance[edge.first]) {
                // * Calculate the minimum Distance
                minimumDistance[edge.first] = nextWeight;
                pq.push({edge.first, nextWeight});

                // * Animation
                addStep(3);
                addEdgeChange(curr.first, edge.first, {0, 1, 1, 1, 0});
                // if (edge.first == dest) return;
            }
        }
    }
}
void addStep(int highlightedLine) {
    steps.push_back(Action());
    steps.back().highlightedLine = highlightedLine;
};

void addNodeChange(int label, ChangeInfo info) {
    steps.back().nodeChange.push_back({label, info});
}

void addEdgeChange(int label1, int label2, ChangeInfo info) {
    steps.back().edgeChange.push_back({label1, label2, info});
}

void addNodeAdd(int label) {
    if (nodeList.find(label) != nodeList.end()) return;
    nodeList.erase(label);
    steps.back().nodeAdded.push_back(label);
}

void addNodeDelete(int label) {
    if (nodeList.find(label) == nodeList.end()) return;
    nodeList.erase(label);
    steps.back().nodeDeleted.push_back(label);
}

void addEdgeAdd(int label1, int label2, int weight) {
    if (label2 < label1) std::swap(label2, label1);

    if (nodeList.find(label1) == nodeList.end()) {
        nodeList.insert(label1);
        steps.back().nodeAdded.push_back(label1);
    }
    if (nodeList.find(label2) == nodeList.end()) {
        nodeList.insert(label2);
        steps.back().nodeAdded.push_back(label2);
    }
    if (edgeList.find({{label1, label2}, weight}) == edgeList.end()) {
        edgeList.insert({{label1, label2}, weight});
        steps.back().edgeAdded.push_back({label1, label2, weight});
    }
}

void addEdgeDelete(int label1, int label2, int weight) {
    if (label2 < label1) std::swap(label2, label1);
    if (edgeList.find({{label1, label2}, weight}) != edgeList.end()) {
        steps.back().edgeDeleted.push_back({label1, label2, weight});
        edgeList.erase({{label1, label2}, weight});
    }
}

ChangeInfo getInfo(std::shared_ptr<GraphEdge> edge, bool isResultHighlight,
                   bool isResultOpaque, bool isImmediate) {
    ChangeInfo res;
    res.isHighlightedBefore = edge->getHighlighted();
    ;
    res.isOpaqueBefore = edge->getOpaque();
    res.isOpaqueAfter = isResultOpaque;
    res.isHighlightedAfter = isResultHighlight;
    res.isImmediate = isImmediate;
    return res;
}
ChangeInfo getInfo(std::shared_ptr<GraphNode> node, bool isResultHighlight,
                   bool isResultOpaque, bool isImmediate) {
    ChangeInfo res;
    res.isHighlightedBefore = node->getHighlighted();
    res.isOpaqueBefore = node->getOpaque();
    res.isOpaqueAfter = isResultOpaque;
    res.isHighlightedAfter = isResultHighlight;
    res.isImmediate = isImmediate;
    return res;
}

void resetGraphColor() {
    for (auto edge : graph.getEdgeList())
        addEdgeChange(edge->node1->getLabel(), edge->node2->getLabel(),
                      getInfo(edge, 0, 1, 1));
    for (auto node : graph.getNodeList())
        addNodeChange(node->getLabel(), getInfo(node, 0, 1, 1));
}
}  // namespace GraphScene
