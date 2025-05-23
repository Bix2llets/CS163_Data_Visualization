#include "graph/graph.h"

#include <cstdlib>
const float Graph::IDEAL_LENGTH = 50.f;
const float Graph::PUSH_FACTOR = 10.f;
const float Graph::PULL_FACTOR = 1.f;
const float Graph::CENTRIC_FACTOR = 10.0f;
void Graph::applyPushForce() {
    // Electrostatic force model
    for (std::shared_ptr<GraphNode> node1 : nodeList)
        for (std::shared_ptr<GraphNode> node2 : nodeList) {
            if (node1->getLabel() >= node2->getLabel()) continue;
            float nodeDistanceSqr =
                Vector2DistanceSqr(node1->getPosition(), node2->getPosition());
            // if (sqrt(nodeDistanceSqr) > IDEAL_LENGTH) continue;
            if (nodeDistanceSqr <= 1e-6) {
                node1->applyForce({1, 0});
                node2->applyForce({-1, 0});
                continue;       
            }
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
    // for (std::shared_ptr<GraphEdge> edge : edgeList) {
    //     float length = edge->getLength();
    //     // float baseLength = 50 * (1 + log10(edge->weight));
    //     float baseLength = IDEAL_LENGTH;
    //     if (length <= baseLength) continue;
    //     float lengthDiff = length - baseLength;
    //     float force = PULL_FACTOR * (lengthDiff);
    //     Vector2 r12 = Vector2Subtract(edge->node2->getPosition(),
    //                                   edge->node1->getPosition());

    //     r12 = Vector2ClampValue(r12, 1.f, 1.f);

    //     edge->node1->applyForce(Vector2Scale(r12, force));
    //     edge->node2->applyForce(Vector2Scale(r12, -force));
    // }
    
    // * Charge model
    for (std::shared_ptr<GraphNode> node1: nodeList) {
        for (std::shared_ptr<GraphNode> node2: nodeList) {
            if (node1->getLabel() >= node2->getLabel()) continue;
            float length = Vector2Distance(node1->getPosition(), node2->getPosition());
            float baseLength = IDEAL_LENGTH;
            // if (length <= baseLength) continue;
            float lengthDiff = length - baseLength;
            float force = PULL_FACTOR * lengthDiff;
            Vector2 r12 = Vector2Subtract(node2->getPosition(), node1->getPosition());
            r12 = Vector2ClampValue(r12, 1.f, 1.f);

            node1->applyForce(Vector2Scale(r12, force));
            node2->applyForce(Vector2Scale(r12, -force));

        }
    } 

}

void Graph::applyCentricForce() {
    // * Gravity model

    int nodeCount = nodeList.size();
    Vector2 centroidPosition = {0, 0};
    for (std::shared_ptr<GraphNode> node : nodeList) {
        centroidPosition = Vector2Add(centroidPosition, node->getPosition());
    }

    centroidPosition = Vector2Scale(centroidPosition, 1.0f / nodeCount);

    Vector2 centerPosition = Vector2Add(AppInfo::UPPER_LEFT, AppInfo::LOWER_RIGHT);

    centerPosition = Vector2Scale(centerPosition, 1.0f / 2);

    Vector2 centricVector = Vector2Subtract(centerPosition, centroidPosition);

    centricVector = Vector2ClampValue(centricVector, 1.0f, 1.0f);

    float distance = Vector2Distance(centerPosition, centroidPosition);

    float force = CENTRIC_FACTOR * distance;

    Vector2 centricForce = Vector2Scale(centricVector, force);

    for (std::shared_ptr<GraphNode> node : nodeList)
        node->applyForce(centricForce);
}

void Graph::handleMouseEvents() {
    Vector2 mousePosition = GetMousePosition();
    bool isMouseDown = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool isMouseReleased = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

    for (auto &node : nodeList) {
        if (isMouseDown && CheckCollisionPointCircle(mousePosition, node->getPosition(), GraphNode::RADIUS)) {
            node->setDragging(true);
        }

        if (isMouseReleased) {
            node->setDragging(false);
        }

        if (node->isDragging()) {
            node->setPosition(mousePosition); // Update position to follow the mouse
            node->setVelocity({0, 0});       // Reset velocity while dragging
        }
    }
}

void Graph::update() {
    handleMouseEvents();
    applyPushForce();
    applyPullForce();
    applyCentricForce();
    for (std::shared_ptr<GraphNode> node : nodeList) {
            node->update();
    }
    for (std::shared_ptr<GraphEdge> edge : edgeList) edge->update();
}

void Graph::render() {
    for (std::shared_ptr<GraphEdge> edge : edgeList)
        if (edge->isHighlighted == false) edge->render();
    for (std::shared_ptr<GraphEdge> edge : edgeList)
        if (edge->isHighlighted == true) edge->render();
    for (std::shared_ptr<GraphNode> node : nodeList) node->render();
    for (std::shared_ptr<GraphEdge> edge : edgeList) edge->renderText();
};

void Graph::addNode(int label) {
    Vector2 newPosition = randomPosition();
    std::shared_ptr<GraphNode> newNode =
        std::make_shared<GraphNode>(label, newPosition.x, newPosition.y);
    for (std::shared_ptr<GraphNode> existedNode : nodeList) {
        if (existedNode->getLabel() == newNode->getLabel()) return;
    }
    nodeList.push_back(newNode);
}

void Graph::addEdge(int node1Label, int node2Label, int weight) {
    if (node1Label == node2Label) return;
    if (node1Label > node2Label) std::swap(node1Label, node2Label);
    addNode(node1Label);
    addNode(node2Label);
    std::shared_ptr<GraphNode> node1 = nullptr, node2 = nullptr;
    for (std::shared_ptr<GraphNode> node : nodeList) {
        if (node->getLabel() == node1Label) node1 = node;
        if (node->getLabel() == node2Label) node2 = node;
    }

    auto existedEdge = findEdge(node1Label, node2Label);
    if (existedEdge) return;
    std::shared_ptr<GraphEdge> newEdge =
        std::make_shared<GraphEdge>(node1, node2, weight);
    edgeList.push_back(newEdge);
}

void Graph::highlightNode(int nodeLabel, bool isImmediate) {
    std::shared_ptr<GraphNode> node = nullptr;
    for (auto existedNode : nodeList) {
        if (existedNode->getLabel() == nodeLabel) {
            node = existedNode;
            break;
        }
    }
    if (node == nullptr) return;
    node->highlight(isImmediate);
}

void Graph::deHighlightNode(int nodeLabel, bool isImmediate) {
    std::shared_ptr<GraphNode> node = nullptr;
    for (auto existedNode : nodeList) {
        if (existedNode->getLabel() == nodeLabel) {
            node = existedNode;
            break;
        }
    }
    if (node == nullptr) return;
    node->deHighlight(isImmediate);
}

void Graph::highlightEdge(int node1Label, int node2Label, bool isImmediate) {
    std::shared_ptr<GraphEdge> edge = findEdge(node1Label, node2Label);
    if (edge == nullptr) return;
    edge->highlight(isImmediate);
}

void Graph::deHighlightEdge(int node1Label, int node2Label, bool isImmediate) {
    std::shared_ptr<GraphEdge> edge = findEdge(node1Label, node2Label);
    if (edge == nullptr) return;
    edge->deHighlight(isImmediate);
}

bool Graph::isAnimationDone() {
    for (std::shared_ptr<GraphNode> node : nodeList)
        if (!node->isCompleted()) return false;

    for (std::shared_ptr<GraphEdge> edge : edgeList)
        if (!edge->isCompleted()) return false;

    return true;
}

std::vector<std::shared_ptr<GraphEdge>> &Graph::getEdgeList() {
    return edgeList;
}

std::vector<std::shared_ptr<GraphNode>> &Graph::getNodeList() {
    return nodeList;
}

void Graph::removeEdge(int node1Label, int node2Label) {
    if (node1Label == node2Label) return;
    if (node1Label > node2Label) std::swap(node1Label, node2Label);
    for (int i = 0; i < edgeList.size(); i++) {
        std::shared_ptr<GraphEdge> edge = edgeList[i];
        if (edge->node1->getLabel() == node1Label &&
            edge->node2->getLabel() == node2Label) {
            edgeList.erase(edgeList.begin() + i);
            return;
        }
    }
}

void Graph::removeNode(int nodeLabel) {
    for (int i = 0; i < nodeList.size(); i++) {
        std::shared_ptr<GraphNode> node = nodeList[i];
        if (node->getLabel() == nodeLabel) {
            nodeList.erase(nodeList.begin() + i);
        }
    }
}

void Graph::finishAnimation() {
    for (std::shared_ptr<GraphNode> node : nodeList) {
        node->finishAnimation();
    }
    for (std::shared_ptr<GraphEdge> edge : edgeList) {
        edge->finishAnimation();
    }
}

void Graph::makeOpaque(int node1Label, int node2Label, bool isImmediate) {
    auto edge = findEdge(node1Label, node2Label);
    if (edge == nullptr) return;
    edge->makeOpaque(isImmediate);
}
void Graph::makeTransparent(int node1Label, int node2Label, bool isImmediate) {
    auto edge = findEdge(node1Label, node2Label);
    if (edge == nullptr) return;
    edge->makeTransparent(isImmediate);
}

std::shared_ptr<GraphEdge> Graph::findEdge(int node1Label, int node2Label) {
    if (node1Label > node2Label) std::swap(node1Label, node2Label);
    for (auto edge : edgeList) {
        if (edge->node1->getLabel() == node1Label &&
            edge->node2->getLabel() == node2Label)
            return edge;
    }
    return nullptr;
}

std::shared_ptr<GraphNode> Graph::findNode(int nodeLabel) {
    for (auto node : nodeList)
        if (node->getLabel() == nodeLabel) return node;
    return nullptr;
}