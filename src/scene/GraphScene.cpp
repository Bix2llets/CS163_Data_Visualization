#include "graphScene.h"

#include <sstream>
#include <unordered_map>
namespace GraphScene {
Graph graph;
std::deque<Action> past;
std::deque<Action> future;
std::deque<Action> steps;
float timeLeft = 0.0f;
const float TIME_DELAY = 0.05f;  // Adjust the delay as needed

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
    addStep();
    addNodeAdd(nodeLabel);
}

void addNode(std::shared_ptr<GraphNode> node) { addNode(node->getLabel()); }

void addEdge(int node1Label, int node2Label, int weight) {
    addStep();
    addEdgeAdd(node1Label, node2Label, weight);
}

void addEdge(std::shared_ptr<GraphNode> node1, std::shared_ptr<GraphNode> node2,
             int weight) {
    addEdge(node1->getLabel(), node2->getLabel(), weight);
}

void removeNode(int nodeLabel) {
    if (graph.findNode(nodeLabel) == nullptr) return;
    addStep();
    addNodeDelete(nodeLabel);
    auto edgeList = graph.getEdgeList();

    for (auto edge : edgeList) {
        if (edge->node1->getLabel() == nodeLabel ||
            edge->node2->getLabel() == nodeLabel)
            addEdgeDelete(edge->node1->getLabel(), edge->node2->getLabel(),
                          edge->getWeight());
    }
}

void removeNode(std::shared_ptr<GraphNode> node) {
    removeNode(node->getLabel());
}

void removeEdge(int node1Label, int node2Label) {
    auto edge = graph.findEdge(node1Label, node2Label);
    if (edge == nullptr) return;
    addStep();
    addEdgeDelete(node1Label, node2Label, edge->getWeight());
}

void removeEdge(std::shared_ptr<GraphNode> node1,
                std::shared_ptr<GraphNode> node2) {
    removeEdge(node1->getLabel(), node2->getLabel());
}

void highlightNode(int nodeLabel, bool isImmediate) {
    if (graph.findNode(nodeLabel) == nullptr) return;
    addStep();
    addNodeChange(nodeLabel, {0, 1, 1, 1, isImmediate});
}

void deHighlightNode(int nodeLabel, bool isImmediate) {
    if (graph.findNode(nodeLabel) == nullptr) return;
    addStep();
    addNodeChange(nodeLabel, {1, 0, 1, 1, isImmediate});
}

void highlightEdge(int node1Label, int node2Label, bool isImmediate) {
    if (graph.findEdge(node1Label, node2Label) == nullptr) return;
    addStep();
    addEdgeChange(node1Label, node2Label, {0, 1, 1, 1, isImmediate});
}

void deHighlightEdge(int node1Label, int node2Label, bool isImmediate) {
    if (graph.findEdge(node1Label, node2Label) == nullptr) return;
    addStep();
    addEdgeChange(node1Label, node2Label, {1, 0, 1, 1, isImmediate});
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

    for (int label : lastAction.nodeAdded) graph.removeNode(label);
    for (int label : lastAction.nodeDeleted) graph.addNode(label);
    for (auto [label1, label2, weight] : lastAction.edgeAdded)
        graph.removeEdge(label1, label2);
    for (auto [label1, label2, weight] : lastAction.edgeDeleted)
        graph.addEdge(label1, label2, weight);

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

        addNode(result.second);
    }

    if (AppMenu::buttonPanel[1][0].isPressed()) {
        auto result = AppMenu::valueBox.getValue();
        if (result.first == false) return;

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
        int node1Label = std::stoi(node1Str);
        int node2Label = std::stoi(node2Str);
        removeEdge(node1Label, node2Label);
    }

    if (AppMenu::buttonPanel[2][0].isPressed()) {
        MST();
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
    addStep();
    for (auto edge : graph.getEdgeList()) {
        ChangeInfo info = getInfo(edge, 0, 0, 0);
        addEdgeChange(edge->node1->getLabel(), edge->node2->getLabel(), info);
    }

    for (auto node : graph.getNodeList()) {
        ChangeInfo info = getInfo(node, 0, 1, 1);
        addNodeChange(node->getLabel(), info);
    }
    for (std::shared_ptr<GraphEdge> edge : edgeList) {
        int label1 = edge->node1->getLabel();
        int label2 = edge->node2->getLabel();
        int prevState1 = parList[label1];
        int prevState2 = parList[label2];
        if (join(label1, label2, parList)) {
            {
                addStep();
                addEdgeChange(label1, label2, ChangeInfo{0, 1, 0, 1, 0});
                if (prevState1 == -1) {
                    addStep();
                    addNodeChange(label1, getInfo(edge->node1, 1, 1, 0));
                }
                if (prevState2 == -1) {
                    addStep();
                    addNodeChange(label2, getInfo(edge->node2, 1, 1, 0));
                }
            }
        } else {
            restoreList.push_back(edge);
        }
    }
    addStep();
    for (auto edge : restoreList) {
        addEdgeChange(edge->node1->getLabel(), edge->node2->getLabel(),
                      getInfo(edge, 0, 1, 0));
    }
}

void dijkstra(int source, int dest) {}
void addStep() { steps.push_back(Action()); }

void addNodeChange(int label, ChangeInfo info) {
    steps.back().nodeChange.push_back({label, info});
}

void addEdgeChange(int label1, int label2, ChangeInfo info) {
    steps.back().edgeChange.push_back({label1, label2, info});
}

void addNodeAdd(int label) { steps.back().nodeAdded.push_back(label); }

void addNodeDelete(int label) { steps.back().nodeDeleted.push_back(label); }

void addEdgeAdd(int label1, int label2, int weight) {
    steps.back().edgeAdded.push_back({label1, label2, weight});
}

void addEdgeDelete(int label1, int label2, int weight) {
    steps.back().edgeDeleted.push_back({label1, label2, weight});
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
    ;
    res.isOpaqueBefore = node->getOpaque();
    res.isOpaqueAfter = isResultOpaque;
    res.isHighlightedAfter = isResultHighlight;
    res.isImmediate = isImmediate;
    return res;
}
}  // namespace GraphScene
