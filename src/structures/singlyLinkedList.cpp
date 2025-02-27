
#include "singlyLinkedList.h"

const ColorSet SLL::NODE_PALETTE = ColorSet{BLACK, BLACK, WHITE, WHITE, BLACK, GOLD};
const int SLL::NODE_RADIUS = 30;
const int SLL::DISTANCE_HORIZONTAL = 80;
const int SLL::DISTANCE_VERTICAL = 80;

SLL::SLL(Rectangle area, float animationRate):
drawArea{area}, animationRate{animationRate}, root{nullptr}, nodePerRow{int(1 + area.width / DISTANCE_HORIZONTAL)}, nodeCount{0} {}
void SLL::update() {
    Node* curr = root;
    while (curr) {
        curr->update();
        curr = curr->nextNode;
    }
}

SLL::SLL(const SLL &sll) {
    nodePerRow = sll.nodePerRow;
    drawArea = sll.drawArea;
    nodeCount = sll.nodeCount;
    animationRate = sll.animationRate;

    root = nullptr;
    Node* sllPtr = sll.root;
    Node* currPtr = root;
    while(sllPtr) {
        if (root == nullptr) {
            root = new Node(*sllPtr);
            root->nextNode = nullptr;
            currPtr = root;
        }
        else {
            currPtr->nextNode = new Node(*sllPtr);
            currPtr = currPtr->nextNode;
            currPtr->nextNode = nullptr;
        }
        sllPtr = sllPtr->nextNode;
    }
}

Node* SLL::addEnd(std::string data) {
    if (root == nullptr) {
        root =
            new Node(data, drawArea.x + NODE_RADIUS, drawArea.y + NODE_RADIUS,
                     NODE_RADIUS, NODE_PALETTE, animationRate);
        nodeCount++;
        return root;
    }

    Node* curr = root;
    while (curr->nextNode) curr = curr->nextNode;
    Vector2 nextTargetPosition =
        getNextNodePosition(curr->getTargetedPosition(), DISTANCE_HORIZONTAL,
                            DISTANCE_VERTICAL, nodePerRow, nodeCount);

    curr->nextNode = new Node(data, nextTargetPosition.x,
                              nextTargetPosition.y + DISTANCE_VERTICAL / 2,
                              NODE_RADIUS, NODE_PALETTE, animationRate);
    curr->nextNode->setTargetedPosition(nextTargetPosition);
    nodeCount++;
    return curr->nextNode;
}

void SLL::render() {
    Node* currEdge = root;
    Node* currNode = root;
    while (currEdge) {
        if (currEdge->nextNode != nullptr) {
            DrawUtility::drawEdge(currEdge->getPosition(),
                                  currEdge->nextNode->getPosition(),
                                  currEdge->edgeColor.getCurrentColor());
            currEdge = currEdge->nextNode;
        } else
            break;
    }
    while (currNode) {
        currNode->render();
        currNode = currNode->nextNode;
    }
}

Vector2 getNextNodePosition(Vector2 currentPosition, int horizontalDistance,
                            int verticalDistance, int nodePerRow,
                            int nodeCount) {
    if (nodeCount % nodePerRow == 0)
        return Vector2{currentPosition.x, currentPosition.y + verticalDistance};
    else if ((nodeCount / nodePerRow) % 2 == 0)
        return Vector2{currentPosition.x + horizontalDistance,
                       currentPosition.y};
    else
        return Vector2{currentPosition.x - horizontalDistance,
                       currentPosition.y};
}

Node* SLL::addAt(std::string data, int place) {
    std::cerr << nodeCount << " " << nodePerRow << "\n";
    if (place == 0) {
        Node* node = new Node(data, drawArea.x + NODE_RADIUS,
                              drawArea.y + NODE_RADIUS - DISTANCE_VERTICAL / 2,
                              NODE_RADIUS, NODE_PALETTE, animationRate);
        node->setTargetedPosition(
            {node->getPosition().x, node->getPosition().y + DISTANCE_VERTICAL / 2});
        Node* curr = root;
        while (curr) {
            if (curr->nextNode != nullptr)
                curr->setTargetedPosition(
                    curr->nextNode->getTargetedPosition());
            else {
                curr->setTargetedPosition(getNextNodePosition(
                    curr->getTargetedPosition(), DISTANCE_HORIZONTAL,
                    DISTANCE_VERTICAL, nodePerRow, nodeCount));
            }
            curr = curr->nextNode;
        }
        node->nextNode = root;
        root = node;
        nodeCount++;
        return root;
    }
    int index = place;
    Node* curr = root;
    place--;
    while (place && curr) {
        curr = curr->nextNode;
        place--;
    }
    if (curr == nullptr) return nullptr;

    Vector2 newPosition =
        getNextNodePosition(curr->getTargetedPosition(), DISTANCE_HORIZONTAL,
                            DISTANCE_VERTICAL, nodePerRow, index);
    Node* node =
        new Node(data, newPosition.x, newPosition.y + DISTANCE_VERTICAL / 2,
                 NODE_RADIUS, NODE_PALETTE, animationRate);
    node->setTargetedPosition(newPosition);

    Node* updatePtr = curr->nextNode;
    while (updatePtr) {
        if (updatePtr->nextNode != nullptr)
            updatePtr->setTargetedPosition(
                updatePtr->nextNode->getTargetedPosition());
        else
            updatePtr->setTargetedPosition(getNextNodePosition(
                updatePtr->getTargetedPosition(), DISTANCE_HORIZONTAL,
                DISTANCE_VERTICAL, nodePerRow, nodeCount));
        updatePtr = updatePtr->nextNode;
    }
    node->nextNode = curr->nextNode;
    curr->nextNode = node;
    nodeCount++;
    return node;
}

void SLL::removeEnd() {
    if (root == nullptr) return;
    if (root->nextNode == nullptr) {
        delete root;
        root = nullptr;
    };
    Node* curr = root;

    while (curr->nextNode->nextNode) curr = curr->nextNode;
    delete curr->nextNode;
    curr->nextNode = nullptr;
    return;
}

void SLL::removeAt(int place) {}

