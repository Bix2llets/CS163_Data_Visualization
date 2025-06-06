#include "graphScene.h"

#include <sstream>
#include <unordered_map>

#include "menu.h"
namespace GraphScene {
Graph graph;
std::deque<Action> past;
std::deque<Action> future;
std::deque<Action> steps;
float timeLeft = 0.0f;
const float TIME_DELAY = 0.0f;
int currentHighlighting = -1;

std::set<int> nodeList;
std::set<std::pair<std::pair<int, int>, int>> edgeList;
const std::vector<std::string> PSEUDO_BLANK;
const std::vector<std::string> PSEUDO_MST = {
    "Remove all edges", "Choose edge of minimum weight", "Join the vertices"};
const std::vector<std::string> PSEUDO_DIJKSTRA = {
    "Set the distance to source to 0", "Set the distance to others to infinity",
    "Choose vertex with minimum distance", "Examine the adjacent vextices"};

MenuPane addPane({0, 0}, &paneBackground, &buttonColorSet, &buttonColorSet);
MenuPane deletePane({0, 0}, &paneBackground, &buttonColorSet, &buttonColorSet);
MenuPane algoPane({0, 0}, &paneBackground, &buttonColorSet, &buttonColorSet);
MenuPane storagePane({0, 0}, &paneBackground, &buttonColorSet, &buttonColorSet);
void setPanePosition(Vector2 position) {
    addPane.setPosition(position);
    deletePane.setPosition(position);
    algoPane.setPosition(position);
    storagePane.setPosition(position);
}

void clearGraph() {
    addStep(-1, nullptr);
    // std::cerr << "Before removal: \n";
    // for (auto x : nodeList) std::cerr << x << " ";
    // std::cerr << "\n";
    // for (auto x : edgeList)
    //     std::cerr << x.first.first << " " << x.first.second << " " <<
    //     x.second
    //               << "\n";
    // std::cerr << "\n";
    std::vector<std::shared_ptr<GraphNode>> graphNodeList = graph.getNodeList();
    std::vector<std::shared_ptr<GraphEdge>> graphEdgeList = graph.getEdgeList();
    for (std::shared_ptr<GraphEdge> edge : graphEdgeList) {
        addEdgeDelete(edge->node1->getLabel(), edge->node2->getLabel(),
                      edge->getWeight());
        graph.removeEdge(edge->node1->getLabel(), edge->node2->getLabel());
    }
    for (std::shared_ptr<GraphNode> node : graphNodeList) {
        addNodeDelete(node->getLabel());
        graph.removeNode(node->getLabel());
    }
    updateAnimation(true);
    graphNodeList.clear();
    graphEdgeList.clear();
    // future.clear();
    edgeList.clear();
    nodeList.clear();
    // std::cerr << graphNodeList.size() << "\n";
    // std::cerr << graphEdgeList.size() << "\n";
    // std::cerr << "After removal: \n";
    // for (auto x : nodeList) std::cerr << x << " ";
    // std::cerr << "\n";
    // for (auto x : edgeList)
    //     std::cerr << x.first.first << " " << x.first.second << " " <<
    //     x.second
    //               << "\n";
    // std::cerr << "\n";
    // std::cerr << "----------------------------\n";
}
void init() {
    addPane.newLine(0, 1, "Vertex", {"Node label"}, {0}, true);
    addPane.newLine(1, 1, "Edge", {"Data"}, {0}, true);
    addPane.newLine(2, 2, "Random", {"Vertices", "Edges"}, {0, 0}, true);

    deletePane.newLine(0, 1, "Vertice", {"Node label"}, {0}, true);
    deletePane.newLine(1, 2, "Edge", {"U", "V"}, {0, 0}, true);
    deletePane.newLine(2, 0, "Clear", {}, {}, false);

    algoPane.newLine(0, 0, "MST", {}, {}, false);
    algoPane.newLine(1, 1, "Dijkstra", {"Source"}, {0}, false);

    storagePane.newLine(0, 0, "Save", {}, {}, false);
    storagePane.newLine(1, 0, "Load", {}, {}, false);

    Form &dataForm = addPane.getForm(1, 0);
    Vector2 dim = dataForm.getDimension();
    dim.x = dim.x * 2 + MenuPane::ELEMENT_DISTANCE.x;
    dataForm.setDimension(dim);
    addPane.calibrate();
    addPane.disable();
    deletePane.disable();
    algoPane.disable();
    storagePane.disable();
}
void updateAnimation(bool isForced) {
    if (!isForced)
        if (!graph.isAnimationDone()) return;
    if (steps.size() == 0) {
        timeLeft = 0;
        currentHighlighting = -1;
    }
    timeLeft -= GetFrameTime();
    if (isForced || (timeLeft <= 0 && steps.size())) {
        Action nextAction = steps.front();
        steps.pop_front();
        past.push_back(nextAction);
        timeLeft = TIME_DELAY;
        currentHighlighting = nextAction.highlightedLine;
        if (nextAction.highlightRef)
            CodePane::loadCode(*nextAction.highlightRef);

        for (NodeChange nodeChange : nextAction.nodeChange) {
            auto node = graph.findNode(nodeChange.label);
            if (node == nullptr) continue;
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
            if (edge == nullptr) continue;
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
void update() {
    graph.update();
    updateAnimation();
}

void render() { graph.render(); }

void addNode(int nodeLabel) {
    if (nodeList.find(nodeLabel) != nodeList.end()) return;
    addStep(-1, nullptr);
    resetGraphColor();
    addNodeAdd(nodeLabel);
}

void addNode(std::shared_ptr<GraphNode> node) { addNode(node->getLabel()); }

void addEdge(int node1Label, int node2Label, int weight) {
    if (edgeList.find({{node1Label, node1Label}, weight}) != edgeList.end())
        return;
    addStep(-1, nullptr);
    resetGraphColor();
    addEdgeAdd(node1Label, node2Label, weight);
}

void addEdge(std::shared_ptr<GraphNode> node1, std::shared_ptr<GraphNode> node2,
             int weight) {
    addEdge(node1->getLabel(), node2->getLabel(), weight);
}

void removeNode(int nodeLabel) {
    if (nodeList.find(nodeLabel) == nodeList.end()) return;
    addStep(-1, nullptr);
    resetGraphColor();
    addNodeDelete(nodeLabel);
    std::vector<std::pair<std::pair<int, int>, int>> deleteList;
    for (auto edge : edgeList) {
        if (edge.first.first == nodeLabel || edge.first.second == nodeLabel)
            deleteList.push_back(edge);
    }

    for (auto edge : deleteList)
        addEdgeDelete(edge.first.first, edge.first.second, edge.second);
}

void removeNode(std::shared_ptr<GraphNode> node) {
    removeNode(node->getLabel());
}

void removeEdge(int node1Label, int node2Label) {
    if (node1Label > node2Label) std::swap(node1Label, node2Label);
    int weight = -1;
    for (auto x : edgeList) {
        if (x.first.first == node1Label && x.first.second == node2Label)
            weight = x.second;
    }
    if (edgeList.find({{node1Label, node2Label}, weight}) == edgeList.end())
        return;
    addStep(-1, nullptr);
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
    // while (steps.size()) {
    //     future.push_front(steps.back());
    //     steps.pop_back();
    // }
    Action lastAction = past.back();
    past.pop_back();
    steps.push_front(lastAction);

    currentHighlighting = lastAction.highlightedLine;
    if (lastAction.highlightRef) CodePane::loadCode(*lastAction.highlightRef);
    for (auto [label1, label2, weight] : lastAction.edgeAdded) {
        graph.removeEdge(label1, label2);
        edgeList.erase({{label1, label2}, weight});
    }
    for (auto [label1, label2, weight] : lastAction.edgeDeleted) {
        graph.addEdge(label1, label2, weight);
        edgeList.insert({{label1, label2}, weight});
    }
    for (int label : lastAction.nodeAdded) {
        graph.removeNode(label);
        nodeList.erase(label);
    }
    for (int label : lastAction.nodeDeleted) {
        graph.addNode(label);
        nodeList.erase(label);
    }

    for (NodeChange nodeChange : lastAction.nodeChange) {
        auto node = graph.findNode(nodeChange.label);
        if (node == nullptr) continue;
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
        if (edge == nullptr) continue;
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
    graph.finishAnimation();
}

void nextStep() {
    if (!steps.size()) return;
    if (steps.size()) {
        updateAnimation();
        graph.finishAnimation();
        timeLeft = 0;
        return;
    }
}

void registerInput() {
    using namespace CodePane;

    if (addPane.isButtonPressed(0)) {
        if (graph.isAnimationDone() == false) return;
        std::string data = addPane.getForm(0, 0).getText();
        addPane.getForm(0, 0).clear();
        if (!isStrNum(data)) return;
        addNode(std::stoi(data));
    }
    if (addPane.isButtonPressed(1)) {
        if (graph.isAnimationDone() == false) return;
        std::string data = addPane.getForm(1, 0).getText();
        addPane.getForm(1, 0).clear();
        std::stringstream ss;
        ss << data;
        std::string u, v, weight;
        ss >> u >> v >> weight;
        if (!isStrNum(u)) return;
        if (!isStrNum(v)) return;
        if (!isStrNum(weight)) return;
        addEdge(std::stoi(u), std::stoi(v), std::stoi(weight));

        return;
    }

    if (addPane.isRandomPressed(0)) {
        int newNodeLabel = rand() % 1000;
        addPane.getForm(0, 0).setText(std::to_string(newNodeLabel));
    }
    if (addPane.isButtonPressed(2)) {
        if (graph.isAnimationDone() == false) return;
        clearGraph();
        addStep(-1, nullptr);
        int maxNode, maxEdge;

        std::string verticesCount = addPane.getText(2, 0);
        std::string edgesCount = addPane.getText(2, 1);
        if (verticesCount.length() == 0 && edgesCount.length() == 0) {
            maxNode = rand() % 20 + 5;
            maxEdge = rand() % std::min((maxNode * (maxNode - 1) / 2), 20);
        } else {
            if (verticesCount.length() == 0) {
                maxNode = rand() % 15;
                if (edgesCount.length() != 0)
                    maxNode += int(sqrt(stoi(edgesCount) * 2));
            } else
                maxNode = std::stoi(verticesCount);
            if (edgesCount.length() == 0)
                maxEdge = rand() % maxNode * (maxNode - 1) / 2;
            else
                maxEdge = std::min(maxNode * (maxNode - 1) / 2,
                                   std::stoi(edgesCount));
            addPane.getForm(2, 0).clear();
            addPane.getForm(2, 1).clear();
        }
        for (int i = 1; i <= maxNode; i++) addNodeAdd(i);
        std::vector<Action::EdgeInfo> edgeList;
        for (int i = 1; i <= maxNode; i++)
            for (int j = i + 1; j <= maxNode; j++)
                edgeList.push_back({i, j, rand()});

        sort(edgeList.begin(), edgeList.end(),
             [](Action::EdgeInfo a, Action::EdgeInfo b) {
                 return a.weight < b.weight;
             });
        for (int i = 0; i < maxEdge; i++) {
            int u = edgeList[i].node1;
            int v = edgeList[i].node2;
            int weight = rand() % 1000;
            addEdgeAdd(u, v, weight);
        }
        updateAnimation(true);
        return;
    }

    if (addPane.isRandomPressed(1)) {
        Form &form = addPane.getForm(1, 0);
        auto nodeList = graph.getNodeList();
        if (nodeList.size() < 2) return;
        int firstNodePlace = rand() % nodeList.size();
        int secondNodePlace = rand() % nodeList.size();
        while (secondNodePlace == firstNodePlace)
            secondNodePlace = rand() % nodeList.size();
        int weight = rand() % 10000;
        std::stringstream ss;
        ss << nodeList[firstNodePlace]->getLabel() << " ";
        ss << nodeList[secondNodePlace]->getLabel() << " ";
        ss << weight;
        std::string str = ss.str();
        form.setText(str);
    }

    if (addPane.isRandomPressed(2)) {
        Form &verticesForm = addPane.getForm(2, 0);
        Form &edgesForm = addPane.getForm(2, 1);

        int nodeCount = rand() % 15 + 5;
        int edgeCount = rand() % (nodeCount * (nodeCount - 1) / 2);
        verticesForm.setText(std::to_string(nodeCount));
        edgesForm.setText(std::to_string(edgeCount));
    }
    if (deletePane.isButtonPressed(0)) {
        if (graph.isAnimationDone() == false) return;
        std::string data = deletePane.getForm(0, 0).getText();
        deletePane.getForm(0, 0).clear();
        if (!isStrNum(data)) return;
        removeNode(std::stoi(data));
        return;
    }

    if (deletePane.isButtonPressed(1)) {
        if (graph.isAnimationDone() == false) return;
        std::string u = deletePane.getForm(1, 0).getText();
        std::string v = deletePane.getForm(1, 1).getText();
        deletePane.getForm(1, 0).clear();
        deletePane.getForm(1, 1).clear();
        if (!isStrNum(u)) return;
        if (!isStrNum(v)) return;
        removeEdge(std::stoi(u), std::stoi(v));
        return;
    }

    if (deletePane.isButtonPressed(2)) {
        if (graph.isAnimationDone() == false) return;
        // * For clearing graph
        clearGraph();
        return;
    }

    if (deletePane.isRandomPressed(0)) {
        auto nodeList = graph.getNodeList();
        if (nodeList.size() == 0) return;
        int place = rand() % nodeList.size();
        Form &form = deletePane.getForm(0, 0);
        form.setText(std::to_string(nodeList[place]->getLabel()));
    }

    if (deletePane.isRandomPressed(1)) {
        auto edgeList = graph.getEdgeList();
        if (edgeList.size() == 0) return;
        int place = rand() % edgeList.size();
        deletePane.getForm(1, 0).setText(
            std::to_string(edgeList[place]->node1->getLabel()));
        deletePane.getForm(1, 1).setText(
            std::to_string(edgeList[place]->node2->getLabel()));
    }
    if (algoPane.isButtonPressed(0)) {
        if (graph.isAnimationDone() == false) return;
        MST();
        return;
    }

    if (algoPane.isButtonPressed(1)) {
        if (graph.isAnimationDone() == false) return;
        std::string data = algoPane.getForm(1, 0).getText();
        algoPane.getForm(1, 0).clear();
        if (!isStrNum(data)) return;
        if (data.find(' ') != std::string::npos) return;
        dijkstra(std::stoi(data));
    }

    if (storagePane.isButtonPressed(0)) {
        if (graph.isAnimationDone() == false) return;
        // * Save function
        const char *filePath = tinyfd_saveFileDialog(
            "Save Graph", "graph.txt", 1, (const char *[]){"*.txt"},
            "Text files (*.txt)");
        if (filePath) {
            std::ofstream outFile(filePath);
            if (!outFile) {
                tinyfd_messageBox("Error", "Failed to open file for saving.",
                                  "ok", "error", 1);
                return;
            }

            // Save nodes
            outFile << "Nodes:\n";
            for (int node : nodeList) {
                outFile << node << "\n";
            }

            // Save edges
            outFile << "Edges:\n";
            for (const auto &edge : edgeList) {
                outFile << edge.first.first << " " << edge.first.second << " "
                        << edge.second << "\n";
            }

            outFile.close();
            // tinyfd_messageBox("Success", "Graph saved successfully.", "ok",
            // "info", 1);
        }
        return;
    }

    if (storagePane.isButtonPressed(1)) {
        if (graph.isAnimationDone() == false) return;
        // * Load function
        const char *filePath = tinyfd_openFileDialog(
            "Load Graph", "graph.txt", 1, (const char *[]){"*.txt"},
            "Text files (*.txt)", 0);
        if (filePath) {
            std::ifstream inFile(filePath);
            if (!inFile) {
                tinyfd_messageBox("Error", "Failed to open file for loading.",
                                  "ok", "error", 1);
                return;
            }

            clearGraph();

            std::string line;
            bool readingNodes = false, readingEdges = false;

            while (std::getline(inFile, line)) {
                if (line == "Nodes:") {
                    readingNodes = true;
                    readingEdges = false;
                    continue;
                } else if (line == "Edges:") {
                    readingNodes = false;
                    readingEdges = true;
                    continue;
                }

                if (readingNodes) {
                    if (!isStrNum(line)) continue;
                    addNode(std::stoi(line));
                } else if (readingEdges) {
                    std::stringstream ss(line);
                    int u, v, weight;
                    ss >> u >> v >> weight;
                    if (ss.fail()) continue;
                    addEdge(u, v, weight);
                }
            }

            inFile.close();
        }
        return;
    }

    if (MenuTable::prevButton.isPressed()) {
        prevStep();
        return;
    }
    if (MenuTable::nextButton.isPressed()) {
        nextStep();
        return;
    }
    if (MenuTable::backwardButton.isPressed()) {
        backward();
        return;
    }
    if (MenuTable::forwardButton.isPressed()) {
        forward();
        return;
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
    addStep(-1, nullptr);
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
    addStep(-1, &PSEUDO_MST);
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
                addStep(1, &PSEUDO_MST);
                addEdgeChange(label1, label2, ChangeInfo{0, 1, 0, 1, 0});
                if (prevState1 == -1) {
                    addStep(2, &PSEUDO_MST);
                    addNodeChange(label1, getInfo(edge->node1, 1, 1, 0));
                }
                if (prevState2 == -1) {
                    addStep(2, &PSEUDO_MST);
                    addNodeChange(label2, getInfo(edge->node2, 1, 1, 0));
                }
            }
        } else {
            restoreList.push_back(edge);
        }
    }
    addStep(-1, &PSEUDO_MST);
    for (auto edge : restoreList) {
        addEdgeChange(edge->node1->getLabel(), edge->node2->getLabel(),
                      {0, 0, 0, 1, 0});
    }
}

void dijkstra(int source) {
    // * Build the adjacency list (undirected) and init the minimumDistance to
    // nodes
    if (nodeList.find(source) == nodeList.end()) return;
    addStep(-1, nullptr);
    resetGraphColor();
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjList;
    std::unordered_map<int, int> minimumDistance;
    const int INF = int(1e9 + 7);
    for (auto node : graph.getNodeList()) {
        adjList[node->getLabel()].resize(0);

        if (node->getLabel() != source) {
            addStep(1, &PSEUDO_DIJKSTRA);
            minimumDistance[node->getLabel()] = INF;
            addNodeChange(node->getLabel(), {0, 1, 1, 1, 0});
        }
    }
    addStep(0, &PSEUDO_DIJKSTRA);
    minimumDistance[source] = 0;
    addNodeChange(source, {0, 1, 1, 1, 0});

    addStep(0, &PSEUDO_DIJKSTRA);
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
        addStep(2, &PSEUDO_DIJKSTRA);
        addNodeChange(curr.first, getInfo(graph.findNode(curr.first), 1, 1, 0));
        // * Traverse the adjacency list
        for (std::pair<int, int> edge : adjList[curr.first]) {
            int nextWeight = curr.second + edge.second;
            if (nextWeight < minimumDistance[edge.first]) {
                // * Calculate the minimum Distance
                minimumDistance[edge.first] = nextWeight;
                pq.push({edge.first, nextWeight});

                // * Animation
                addStep(3, &PSEUDO_DIJKSTRA);
                addEdgeChange(curr.first, edge.first, {0, 1, 1, 1, 0});
            }
        }
    }
}
void addStep(int highlightedLine, std::vector<std::string> const *ref) {
    steps.push_back(Action());
    steps.back().highlightedLine = highlightedLine;
    steps.back().highlightRef = ref;
};

void addNodeChange(int label, ChangeInfo info) {
    steps.back().nodeChange.push_back({label, info});
}

void addEdgeChange(int label1, int label2, ChangeInfo info) {
    steps.back().edgeChange.push_back({label1, label2, info});
}

void addNodeAdd(int label) {
    if (nodeList.find(label) != nodeList.end()) return;
    nodeList.insert(label);
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
    for (auto x : edgeList)
        if (x.first.first == label1 && x.first.second == label2) return;
    edgeList.insert({{label1, label2}, weight});
    steps.back().edgeAdded.push_back({label1, label2, weight});
}

void addEdgeDelete(int label1, int label2, int weight) {
    if (label2 < label1) std::swap(label2, label1);
    for (auto x : edgeList)
        if (x.first.first == label1 && x.first.second == label2) {
            steps.back().edgeDeleted.push_back({label1, label2, weight});
            edgeList.erase({{label1, label2}, weight});
            return;
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

void backward() {
    while (past.size()) {
        prevStep();
        while (steps.size()) steps.pop_back();
        if (past.size() == 0 || steps.front().highlightRef == nullptr) return;
    }
}

void forward() {
    while (steps.size()) {
        nextStep();
        if (past.back().highlightRef == nullptr) return;
    }
}
}  // namespace GraphScene
