#include "graph/graph.h"

#include <cstdlib>
const float Graph::IDEAL_LENGTH = 100.f;
const float Graph::PUSH_FACTOR = 1.f;
const float Graph::PULL_FACTOR = 1.f;
const float Graph::CENTRIC_FACTOR = 1.0f;
void Graph::applyPushForce() {
    // Electrostatic force model
    for (std::shared_ptr<GraphNode> node1 : nodeList)
        for (std::shared_ptr<GraphNode> node2 : nodeList) {
            if (node1->getLabel() >= node2->getLabel()) continue;
            float nodeDistanceSqr =
                Vector2DistanceSqr(node1->getPosition(), node2->getPosition());
            Vector2 r12 =
                Vector2Subtract(node2->getPosition(), node1->getPosition());
            r12 = Vector2ClampValue(r12, 1.f, 1.f);
            float force = PUSH_FACTOR / nodeDistanceSqr * (1000 * 1000);
            node1->applyForce(Vector2Scale(r12, -force));
            node2->applyForce(Vector2Scale(r12, force));
        }
}

void Graph::applyPullForce() {

    // * Spring model
    for (std::shared_ptr<GraphEdge> edge: edgeList) {
        float length = edge->getLength();
        if (length <= IDEAL_LENGTH) continue;
        float lengthDiff = length - IDEAL_LENGTH;
        float force = PULL_FACTOR * (lengthDiff);
        Vector2 r12 = Vector2Subtract(edge->node2->getPosition(), edge->node1->getPosition());

        r12 = Vector2ClampValue(r12, 1.f, 1.f);

        edge->node1->applyForce(Vector2Scale(r12, force));
        edge->node2->applyForce(Vector2Scale(r12, -force));
    }

    // * Charge model
}

void Graph::applyCentricForce() {
    // * Gravity model
    
    int nodeCount = nodeList.size();
    Vector2 centroidPosition = {0, 0};
    for (std::shared_ptr<GraphNode> node: nodeList) {
        centroidPosition = Vector2Add(centroidPosition, node->getPosition());
    }

    centroidPosition = Vector2Scale(centroidPosition, 1.0f / nodeCount);

    Vector2 centerPosition = Vector2Add(Loop::UPPER_LEFT, Loop::LOWER_RIGHT);

    centerPosition = Vector2Scale(centerPosition, 1.0f / 2);

    Vector2 centricVector = Vector2Subtract(centerPosition, centroidPosition);

    centricVector = Vector2ClampValue(centricVector, 1.0f, 1.0f);

    float distance = Vector2Distance(centerPosition, centroidPosition);

    float force = CENTRIC_FACTOR * distance;

    Vector2 centricForce = Vector2Scale(centricVector, force);

    for (std::shared_ptr<GraphNode> node: nodeList) node->applyForce(centricForce);

}
void Graph::update() {
    applyPushForce();
    applyPullForce();
    applyCentricForce();
    for (std::shared_ptr<GraphNode> node: nodeList) node->update();
    for (std::shared_ptr<GraphEdge> edge: edgeList) edge->update();
};

void Graph::render() {
    for (std::shared_ptr<GraphEdge> edge : edgeList) edge->render();
    for (std::shared_ptr<GraphNode> node : nodeList) node->render();
};

void Graph::addNode(std::shared_ptr<GraphNode> node) {
    for (std::shared_ptr<GraphNode> existedNode : nodeList) {
        if (existedNode->getLabel() == node->getLabel()) return;
    }
    nodeList.push_back(node);
}

void Graph::addNode(int label) {
    Vector2 newPosition = randomPosition();
    std::shared_ptr<GraphNode> newNode = std::make_shared<GraphNode>(label, newPosition.x, newPosition.y);
    addNode(newNode);
}

void Graph::addEdge(std::shared_ptr<GraphNode> node1,
                    std::shared_ptr<GraphNode> node2, int weight) {
    if (node1->getLabel() == node2->getLabel()) {
        std::cerr << "Loop found. Edge creation stopped\n";
        return;
    }

    if (node1->getLabel() > node2->getLabel()) std::swap(node1, node2);
    for (std::shared_ptr<GraphEdge> edge : edgeList) {
        if (edge->node1->getLabel() == node1->getLabel() &&
            edge->node2->getLabel() == node2->getLabel())
            return;
    }
    std::shared_ptr<GraphEdge> newEdge =
        std::make_shared<GraphEdge>(node1, node2, weight);
    edgeList.push_back(newEdge);
}
void Graph::addEdge(int node1Label, int node2Label, int weight) {
    if (node1Label == node2Label) return;
    addNode(node1Label);
    addNode(node2Label);
    std::shared_ptr<GraphNode> node1, node2;
    for (std::shared_ptr<GraphNode> node: nodeList) {
        if (node->getLabel() == node1Label) node1 = node;
        if (node->getLabel() == node2Label) node2 = node; 
    }
    addEdge(node1, node2, weight);
}

void Graph::highlightNode(std::shared_ptr<GraphNode> node) {
    node->highlight();
}
void Graph::deHighlightNode(std::shared_ptr<GraphNode> node) {
    node->deHighlight();
}

void Graph::highlightEdge(std::shared_ptr<GraphEdge> edge) {
    edge->highlight();
}

void Graph::deHighlightEdge(std::shared_ptr<GraphEdge> edge) {
    edge->deHighlight();
}

bool Graph::isAnimationDone() {
    for (std::shared_ptr<GraphNode> node : nodeList)
        if (!node->isCompleted()) return false;

    for (std::shared_ptr<GraphEdge> edge : edgeList)
        if (!edge->isCompleted()) return false;

    return true;
}

std::vector<std::shared_ptr<GraphEdge>> Graph::getEdgeList() {
    return edgeList;
}