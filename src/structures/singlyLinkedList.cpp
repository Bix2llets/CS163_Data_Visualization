#include "singlyLinkedList.h"

SinglyLinkedList::Node::~Node() {
    if (nextNode != nullptr) nextNode->~Node();
    delete nextNode;
}

void SinglyLinkedList::Node::render() {
    if (PALETTE.renderBorder) {
        DrawCircle(position.x, position.y, RADIUS, PALETTE.border);
        DrawCircle(position.x, position.y, RADIUS - 3,
                   PALETTE.backgroundNormal);
    } else
        DrawCircle(position.x, position.y, RADIUS, PALETTE.backgroundNormal);
    DrawUtility::drawText(data, position, DrawUtility::inter20,
                          PALETTE.textNormal, DrawUtility::NORMAL_SIZE,
                          DrawUtility::SPACING,
                          DrawUtility::VerticalAlignment::CENTERED,
                          DrawUtility::HorizontalAlignment::CENTERED);
}

Vector2 SinglyLinkedList::Node::getLeftMost() const {
    return Vector2Add(position, Vector2{-RADIUS, 0});
}

Vector2 SinglyLinkedList::Node::getRightMost() const {
    return Vector2Add(position, Vector2{RADIUS, 0});
}

Vector2 SinglyLinkedList::Node::getTopMost() const {
    return Vector2Add(position, Vector2{0, -RADIUS});
}

Vector2 SinglyLinkedList::Node::getBottomMost() const {
    return Vector2Add(position, Vector2{0, RADIUS});
}

void SinglyLinkedList::addNode(int data, bool isInstant) {
    addNode(std::to_string(data), isInstant);
}

void SinglyLinkedList::addNode(std::string data, bool isInstant) {
    countNode++;
    Node* curr = root;
    if (curr != nullptr) {
        while (curr->nextNode != nullptr) curr = curr->nextNode;
        Vector2 nextNodePosition = curr->getPosition();
        nextNodePosition = Vector2Add(
            nextNodePosition, Vector2{RADIUS * 2 + HORIZONTAL_DISTANCE, 0});
        curr->nextNode = new Node(data, nextNodePosition.x, nextNodePosition.y,
                                  RADIUS, PALETTE, currentColor);
        if (isInstant) {
            curr->nextNodeEdge.setEndPosition(curr->nextNode->getPosition());
            curr->nextNodeEdge.setMotionEndPosition(
                curr->nextNode->getPosition());
        } else {
            curr->nextNodeEdge.setMotionEndPosition(
                curr->nextNode->getPosition());
            curr->nextNodeEdge.setEndPosition(curr->getPosition());
        }
        curr->nextNode->setAnimationRate(animationRate);
        return;
    }
    root = new Node(data, position.x, position.y, RADIUS, PALETTE);
    root->setAnimationRate(animationRate);
}

void SinglyLinkedList::render() {
    Node* animCurr = root;
    Node* nodeCurr = root;
    if (root != nullptr)
        DrawUtility::drawText(
            "Head",
            Vector2Add(root->getPosition(),
                       Vector2Scale({0, VERTICAL_DISTANCE}, 0.5)),
            DrawUtility::inter20, PALETTE.textHighlight,
            DrawUtility::NORMAL_SIZE, DrawUtility::SPACING,
            DrawUtility::VerticalAlignment::CENTERED,
            DrawUtility::HorizontalAlignment::CENTERED);
    while (animCurr) {
        if (animCurr->nextNode) animCurr->nextNodeEdge.render();
        if (animCurr->isMotionCompleted())
            animCurr = animCurr->nextNode;
        else
            break;
    }
    while (nodeCurr) {
        nodeCurr->render();
        if (nodeCurr->isMotionCompleted())
            nodeCurr = nodeCurr->nextNode;
        else
            break;
    }
}

void SinglyLinkedList::removeEnd() {
    countNode--;
    Node* curr = root;
    if (curr == nullptr) return;
    if (curr->nextNode == nullptr) {
        delete curr;
        root = nullptr;
        return;
    }
    Node* prev = nullptr;
    while (curr->nextNode) {
        prev = curr;
        curr = curr->nextNode;
    }

    delete curr;
    prev->nextNode = nullptr;
}

void SinglyLinkedList::Node::updateMotion() {
    nextNodeEdge.updateMotion();
    // if (nextNodeEdge.isCompleted() && nextNode) nextNode->update();
}

void SinglyLinkedList::Node::updateColor() {
    nextNodeEdge.updateColor();
}

void SinglyLinkedList::Node::setAnimationRate(float rate) {
    nextNodeEdge.setMotionUpdateRate(rate);
    if (nextNode != nullptr) {
        nextNode->setAnimationRate(rate);
    }
}

void SinglyLinkedList::Node::resetAnimation() {
    if (nextNode == nullptr) return;
    nextNodeEdge.setEndPosition(position);
    nextNodeEdge.setMotionEndPosition(nextNode->position);
}

bool SinglyLinkedList::Node::isMotionCompleted() {
    return nextNodeEdge.isMotionCompleted();
}

void SinglyLinkedList::update() {
    currentColor.update();
    Node* curr = root;
    while (curr) {
        curr->updateMotion();
        if (curr->isMotionCompleted())
            curr = curr->nextNode;
        else
            break;
    }
    curr = root;
    while(curr) {
        curr->updateColor();
        curr = curr -> nextNode;
    }
}

void SinglyLinkedList::setAnimationRate(float rate) {
    animationRate = rate;
    if (root != nullptr) root->setAnimationRate(rate);
}

void SinglyLinkedList::resetAnimation() {
    Node* curr = root;
    while (curr) {
        // curr->nextNodeEdge.setMotionEndPosition(curr->nextNodeEdge.getEndPosition());
        curr->nextNodeEdge.setEndPosition(
            curr->nextNodeEdge.getBeginPosition());
        curr = curr->nextNode;
    }
}

void SinglyLinkedList::setHighlight(bool highlight) {
    currentColor.setFactor(0.f);
    if (highlight) {
        currentColor.setBaseColor(DrawUtility::EDGE_NORMAL);
        currentColor.setTargetColor(DrawUtility::EDGE_HIGHLIGHTED);
    } else {
        currentColor.setBaseColor(DrawUtility::EDGE_HIGHLIGHTED);
        currentColor.setTargetColor(DrawUtility::EDGE_NORMAL);
    }
    Node* curr = root;
    while (curr) {
        curr->nextNodeEdge.setHighlight(highlight);
        curr = curr->nextNode;
    }
}
