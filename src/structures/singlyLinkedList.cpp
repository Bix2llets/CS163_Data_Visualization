
#include "singlyLinkedList.h"

const ColorSet SLL::NODE_PALETTE =
    ColorSet{BLACK, BLACK, WHITE, WHITE, BLACK, GOLD};
const int SLL::NODE_RADIUS = 30;
const int SLL::DISTANCE_HORIZONTAL = 80;
const int SLL::DISTANCE_VERTICAL = 80;

SLL::SLL(Rectangle area, float animationRate)
    : drawArea{area},
      animationRate{animationRate},
      root{nullptr},
      nodePerRow{int(1 + area.width / DISTANCE_HORIZONTAL)},
      nodeCount{0} {}
void SLL::update() {
    Node* curr = root;
    while (curr) {
        curr->update();
        curr = curr->nextNode;
    }
}

SLL::SLL(const SLL& sll) {
    nodePerRow = sll.nodePerRow;
    drawArea = sll.drawArea;
    nodeCount = sll.nodeCount;
    animationRate = sll.animationRate;

    root = sll.root;
}

void SLL::addEnd(std::string data) {
    if (root == nullptr) {
        root =
            new Node(data, drawArea.x + NODE_RADIUS - DISTANCE_HORIZONTAL / 2, drawArea.y + NODE_RADIUS - DISTANCE_VERTICAL / 2,
                     NODE_RADIUS, NODE_PALETTE, animationRate);
        root->setTargetedPosition({drawArea.x + NODE_RADIUS, drawArea.y + NODE_RADIUS});
        nodeCount++;
        return;
    }

    Node* curr = root;
    while (curr->nextNode) curr = curr->nextNode;
    Vector2 nextTargetPosition =
        getNextNodePosition(curr->getTargetedPosition(), DISTANCE_HORIZONTAL,
                            DISTANCE_VERTICAL, nodePerRow, nodeCount);

    curr->nextNode = new Node(data, nextTargetPosition.x - DISTANCE_HORIZONTAL / 2,
                              nextTargetPosition.y - DISTANCE_VERTICAL / 2,
                              NODE_RADIUS, NODE_PALETTE, animationRate);
    curr->nextNode->setTargetedPosition(nextTargetPosition);
    nodeCount++;
    return;
}

void SLL::render() {
    if (root == nullptr) return;
    DrawUtility::drawText(
        "Root", Vector2Add(root->getPosition(), {0, DISTANCE_HORIZONTAL / 2}),
        DrawUtility::inter20, BLACK, DrawUtility::NORMAL_SIZE,
        DrawUtility::SPACING, VerticalAlignment::CENTERED,
        HorizontalAlignment::CENTERED);
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

void SLL::addAt(std::string data, int place) {
    std::cerr << nodeCount << " " << nodePerRow << "\n";
    place--;
    if (place == 0) {
        Node* node = new Node(data, drawArea.x + NODE_RADIUS - DISTANCE_HORIZONTAL / 2,
                              drawArea.y + NODE_RADIUS - DISTANCE_VERTICAL / 2,
                              NODE_RADIUS, NODE_PALETTE, animationRate);
        node->setTargetedPosition(
            {drawArea.x + NODE_RADIUS, drawArea.y + NODE_RADIUS});
        if (root == nullptr) {
            root = node;
            return;
        }
        Node* curr = root;
        node->nextNode = root;
        root = node;
        nodeCount++;
        return;
    }
    int index = place;
    Node* curr = root;
    place--;
    while (place && curr) {
        curr = curr->nextNode;
        place--;
    }
    if (curr == nullptr) return;

    Vector2 newPosition =
        getNextNodePosition(curr->getTargetedPosition(), DISTANCE_HORIZONTAL,
                            DISTANCE_VERTICAL, nodePerRow, index);
    Node* node =
        new Node(data, newPosition.x - DISTANCE_HORIZONTAL / 2, newPosition.y - DISTANCE_VERTICAL / 2,
                 NODE_RADIUS, NODE_PALETTE, animationRate);
    node->setTargetedPosition(newPosition);

    node->nextNode = curr->nextNode;
    curr->nextNode = node;
    nodeCount++;
    return;
}

void SLL::removeEnd() {
    if (root == nullptr) return;
    if (root->nextNode == nullptr) {
        delete root;
        root = nullptr;
        return;
    };
    Node* curr = root;

    while (curr->nextNode->nextNode) curr = curr->nextNode;
    delete curr->nextNode;
    curr->nextNode = nullptr;
    nodeCount--;
    return;
}

void SLL::removeAt(int place) {
    if (place > nodeCount) return;
    place--;
    Node* curr = root;
    Node* prev = nullptr;

    while (place && curr) {
        place--;
        prev = curr;
        curr = curr->nextNode;
    };
    if (curr == nullptr) return;
    if (prev == nullptr) {
        root = curr->nextNode;
        delete curr;
    } else {
        prev->nextNode = curr->nextNode;
        delete (curr);
    }

    nodeCount--;
}

void SLL::shiftForward(int place) {
    if (root == nullptr) return;
    Node* curr = root;
    int index = 1;
    place--;
    while (place && curr) {
        curr = curr->nextNode;
        place--;
        index++;
    };
    if (curr == nullptr) return;

    while (curr) {
        curr->setTargetedPosition(getNextNodePosition(
            curr->getTargetedPosition(), DISTANCE_HORIZONTAL, DISTANCE_VERTICAL,
            nodePerRow, index));
        curr = curr->nextNode;
        index++;
    }
}

void SLL::shiftBackward(int place) {
    if (root == nullptr) return;
    Node* curr = root;
    Node* prev = nullptr;
    int index = 0;
    place--;
    while (place && curr) {
        index++;
        place--;
        prev = curr;
        curr = curr->nextNode;
    }

    if (curr == nullptr) return;
    while (curr) {
        if (curr == root)
            curr->setTargetedPosition(
                {drawArea.x + NODE_RADIUS, drawArea.y + NODE_RADIUS});
        else
            curr->setTargetedPosition(getNextNodePosition(
                prev->getTargetedPosition(), DISTANCE_HORIZONTAL,
                DISTANCE_VERTICAL, nodePerRow, index));
        prev = curr;
        curr = curr->nextNode;
        index++;
    }
}

bool SLL::isFinished() {
    if (root == nullptr) return true;
    Node* curr = root;
    while (curr) {
        if (curr->isFinished() == false) return false;
        curr = curr->nextNode;
    }
    return true;
}

SLL SLL::clone() {
    SLL result;
    result.nodePerRow = nodePerRow;
    result.drawArea = drawArea;
    result.nodeCount = nodeCount;
    result.animationRate = animationRate;

    Node* currPtr = root;
    result.root = nullptr;
    Node* resultPtr = result.root;
    while(currPtr) {
        if (result.root == nullptr) {
            result.root = new Node(*currPtr);
            resultPtr = result.root;
        }
        else {
            resultPtr->nextNode = new Node(*currPtr);
            resultPtr = resultPtr->nextNode;
        }
        currPtr = currPtr->nextNode;
    }
    return result;
}

SLL SLL::operator=(const SLL &source) {
    if (this != &source) {

        nodePerRow = source.nodePerRow;
        drawArea = source.drawArea;
        nodeCount = source.nodeCount;
        animationRate = source.animationRate;
        
        root = source.root;
    }
    return *this;
}

void SLL::finishAnimation() {
    if (root == nullptr) return;
    Node* curr = root;
    while(curr) {
        curr->finishAnimation();
        curr = curr->nextNode;
    }
}

void SLL::setAnimationRate(float rate) {
    animationRate = rate;
    Node* curr = root;
    if (curr == nullptr) return;
    while(curr) {
        curr->setAnimationRate(rate);
        curr = curr->nextNode;
    }
}