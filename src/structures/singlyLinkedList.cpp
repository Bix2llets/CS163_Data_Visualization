
#include "singlyLinkedList.h"
#include "SLLScene.h"
#include "colorPalette.h"
ColorSet const *SLL::NODE_PALETTE = &nodeColorSet;
const int SLL::NODE_RADIUS = 30;
const int SLL::DISTANCE_HORIZONTAL = 120;
const int SLL::DISTANCE_VERTICAL = 120;

SLL::SLL(Rectangle area, float animationRate)
    : drawArea{area},
      animationRate{animationRate},
      root{nullptr},
      nodePerRow{int(1 + area.width / DISTANCE_HORIZONTAL)},
      nodeCount{0} {}
void SLL::update() {
    Node* curr = root;

    // update animation
    while (curr) {
        curr->updateAnimation();
        curr = curr->nextNode;
    }
    // update gradient color
    curr = root;
    while (curr) {
        curr->borderColor.update();
        // std::cerr << curr->borderColor.getAnimationRate() << "\n";
        if (!curr->borderColor.isCompleted()) break;
        curr->edgeColor.update();
        // std::cerr << curr->edgeColor.getAnimationRate() << "\n";
        if (!curr->edgeColor.isCompleted()) break;
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
            new Node(data, drawArea.x + NODE_RADIUS - DISTANCE_HORIZONTAL / 3,
                     drawArea.y + NODE_RADIUS - DISTANCE_VERTICAL / 3,
                     NODE_RADIUS);
        nodeCount++;
        return;
    }

    Node* curr = root;
    int index = 1;
    while (curr->nextNode) {
        curr = curr->nextNode;
        index++;
    }
    Vector2 nextTargetPosition =
        getNextNodePosition(curr->getTargetedPosition(), DISTANCE_HORIZONTAL,
                            DISTANCE_VERTICAL, nodePerRow, index);

    curr->nextNode =
        new Node(data, nextTargetPosition.x - DISTANCE_HORIZONTAL / 3,
                 nextTargetPosition.y - DISTANCE_VERTICAL / 3, NODE_RADIUS);
    nodeCount++;
    return;
}

void SLL::render() {
    if (root == nullptr) return;
    DrawUtility::drawText(
        "Root", Vector2Add(root->getPosition(), {0, DISTANCE_HORIZONTAL / 3}),
        DrawUtility::inter20, NODE_PALETTE->textNormal, DrawUtility::NORMAL_SIZE,
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
    if (place == 0) {
        Node* node =
            new Node(data, drawArea.x + NODE_RADIUS - DISTANCE_HORIZONTAL / 3,
                     drawArea.y + NODE_RADIUS - DISTANCE_VERTICAL / 3,
                     NODE_RADIUS);
        nodeCount++;
        if (root == nullptr) {
            root = node;
            return;
        }
        Node* curr = root;
        node->nextNode = root;
        root = node;
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
    Node* node = new Node(data, newPosition.x - DISTANCE_HORIZONTAL / 3,
                          newPosition.y - DISTANCE_VERTICAL / 3, NODE_RADIUS);

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
        nodeCount--;
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
    Node* curr = root;;
    Node* prev = nullptr;

    if (place == 0) {
        root = root->nextNode;
        delete curr;
        nodeCount--;
        return;
    }
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

void SLL::moveAt(int place) {
    if (place > nodeCount) return;
    // if (place == 0) return;
    // place--;
    Node* curr = root;
    while (place && curr) {
        curr = curr->nextNode;
        place--;
    }
    if (curr == nullptr) return;
    curr->setTargetedPosition(
        Vector2Add(curr->getTargetedPosition(),
                   {DISTANCE_HORIZONTAL / 3, DISTANCE_VERTICAL / 3}));
}

void SLL::moveEnd() {
    Node* curr = root;
    if (curr == nullptr) return;
    while (curr->nextNode) curr = curr->nextNode;
    curr->setTargetedPosition(
        Vector2Add(curr->getTargetedPosition(),
                   {DISTANCE_HORIZONTAL / 3, DISTANCE_VERTICAL / 3}));
}

void SLL::shiftForward(int place) {
    if (root == nullptr) return;
    Node* curr = root;
    int index = 0;
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

    Node* currPtr = root;
    result.root = nullptr;
    Node* resultPtr = result.root;
    while (currPtr) {
        if (result.root == nullptr) {
            result.root = new Node(*currPtr);
            resultPtr = result.root;
        } else {
            resultPtr->nextNode = new Node(*currPtr);
            resultPtr = resultPtr->nextNode;
        }
        currPtr = currPtr->nextNode;
    }
    return result;
}

SLL SLL::operator=(const SLL& source) {
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
    while (curr) {
        curr->finishAnimation();
        curr = curr->nextNode;
    }
}

// SLL::~SLL() {
//     while (root) {
//         Node* curr = root;
//         root = root->nextNode;
//         delete curr;
//     }
// }

int SLL::locate(std::string val) {
    Node* curr = root;
    int place = 0;
    while (curr && curr->data != val) {
        curr = curr->nextNode;
        place++;
    }
    if (curr == nullptr) return -1;
    return place;
}

void SLL::highlightTo(int place) {
    if (place < 0) return;
    Node* curr = root;
    while (curr && place) {
        curr->borderColor.transitionToward(NODE_PALETTE->borderHighlight);
        curr->edgeColor.transitionToward(NODE_PALETTE->borderHighlight);
        curr = curr->nextNode;
        place--;
    }
    if (curr == nullptr) return;
    curr->borderColor.transitionToward(NODE_PALETTE->borderHighlight);
}

void SLL::deHighlight() {
    Node* curr = root;
    Color normalColor = NODE_PALETTE->borderNormal;
    while (curr) {
        curr->borderColor.setBaseColor(normalColor);
        curr->borderColor.setCurrentColor(normalColor);
        curr->borderColor.setTargetColor(normalColor);
        curr->borderColor.setFactor(1.f);
        curr->edgeColor.setBaseColor(normalColor);
        curr->edgeColor.setCurrentColor(normalColor);
        curr->edgeColor.setTargetColor(normalColor);
        curr->edgeColor.setFactor(1.f);
        curr = curr->nextNode;
    }
}

void SLL::freeMemory() {
    while(root) {
        Node* curr = root;
        root = root->nextNode;
        delete curr;
    }
}

std::string SLL::getSaveData() {
    Node* curr = root;
    std::string res;
    while(curr) {
        res = res + curr->data;
        if (curr->nextNode) res = res + " ";
        curr = curr->nextNode;
    }
    return res;
}