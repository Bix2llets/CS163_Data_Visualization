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
    TextUtility::drawText(data, position, TextUtility::inter20,
                          PALETTE.textNormal, TextUtility::NORMAL_SIZE,
                          TextUtility::SPACING,
                          TextUtility::VerticalAlignment::CENTERED,
                          TextUtility::HorizontalAlignment::CENTERED);
    if (nextNode != nullptr) {
        Vector2 beginPosition = getRightMost();
        Vector2 endPosition = nextNode->getLeftMost();
        DrawLineEx(beginPosition, endPosition, 3, PALETTE.border);
        nextNode->render();
    }
}

Vector2 SinglyLinkedList::Node::getLeftMost() const {
    return Vector2Add(position, Vector2{-RADIUS, 0});
}

Vector2 SinglyLinkedList::Node::getRightMost() const {
    return Vector2Add(position, Vector2{RADIUS, 0});
}

void SinglyLinkedList::addNode(int data) { addNode(std::to_string(data)); }
void SinglyLinkedList::addNode(std::string data) {
    countNode++;
    Node* curr = root;
    if (curr != nullptr) {
        while (curr->nextNode != nullptr) curr = curr->nextNode;
        Vector2 nextNodePosition = curr->getPosition();
        nextNodePosition = Vector2Add(
            nextNodePosition, Vector2{RADIUS * 2 + HORIZONTAL_DISTANCE, 0});
        curr->nextNode = new Node(data, nextNodePosition.x, nextNodePosition.y,
                                  RADIUS, PALETTE);
        return;
    }
    root = new Node(data, position.x, position.y, RADIUS, PALETTE);
}

void SinglyLinkedList::render() {
    Node* curr = root;
    if (root != nullptr)
    TextUtility::drawText(
        "Head", Vector2Add(root->getPosition(),
                           Vector2Scale({0, VERTICAL_DISTANCE}, 0.5)), TextUtility::inter20, PALETTE.textHighlight, TextUtility::NORMAL_SIZE, TextUtility::SPACING, TextUtility::VerticalAlignment::CENTERED, TextUtility::HorizontalAlignment::CENTERED);
    while (curr) {
        curr->render();
        curr = curr->nextNode;
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