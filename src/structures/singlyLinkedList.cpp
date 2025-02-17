#include "singlyLinkedList.h"

SinglyLinkedList::Node::~Node() {
    if (nextNode != nullptr) nextNode->~Node();
    delete nextNode;
}

void SinglyLinkedList::Node::render() {
    float width = parentClass.WIDTH;
    float height = parentClass.HEIGHT;

    Vector2 cornerVector{width, height};

    DrawRectangle(position.x, position.y, cornerVector.x, cornerVector.y,
                  parentClass.PALETTE.backgroundNormal);
    if (parentClass.PALETTE.renderBorder)
        DrawRectangleLines(position.x, position.y, cornerVector.x,
                           cornerVector.y, parentClass.PALETTE.border);
    Vector2 center = Vector2Add(
        position, Vector2Scale({parentClass.WIDTH, parentClass.HEIGHT}, 0.5));
    TextUtility::drawText(data, center, TextUtility::inter20,
                          parentClass.PALETTE.textNormal,
                          TextUtility::NORMAL_SIZE, TextUtility::SPACING,
                          TextUtility::VerticalAlignment::CENTERED,
                          TextUtility::HorizontalAlignment::CENTERED);
    if (nextNode != nullptr) {
        Vector2 beginPosition = getEndPoint();
        Vector2 endPosition = nextNode->getStartPoint();
        DrawLineEx(beginPosition, endPosition, 3, parentClass.PALETTE.border);
        nextNode->render();
    }
}

Vector2 SinglyLinkedList::Node::getStartPoint() const {
    return Vector2Add(position, Vector2{0, parentClass.HEIGHT / 2});
}

Vector2 SinglyLinkedList::Node::getEndPoint() const {
    return Vector2Add(getStartPoint(), Vector2{parentClass.WIDTH, 0});
}

void SinglyLinkedList::addNode(int data) { addNode(std::to_string(data)); }
void SinglyLinkedList::addNode(std::string data) {
    countNode++;
    Node* curr = root;
    if (curr != nullptr) {
        while (curr->nextNode != nullptr) curr = curr->nextNode;
        Vector2 nextNodePosition = curr->getPosition();
        nextNodePosition = Vector2Add(nextNodePosition,
                                      Vector2{WIDTH + HORIZONTAL_DISTANCE, 0});
        curr->nextNode =
            new Node(*this, data, nextNodePosition.x, nextNodePosition.y);
        return;
    }
    root = new Node(*this, data, position.x, position.y);
}

void SinglyLinkedList::render() {
    Node* curr = root;
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