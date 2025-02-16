#include "singlyLinkedList.h"

SinglyLinkedList::Node::~Node() {
    if (nextNode != nullptr) nextNode->~Node();
    delete nextNode;
}

void SinglyLinkedList::Node::render() {
    float width = parentClass.width;
    float height = parentClass.height;

    Vector2 cornerVector{width, height};
    double angle;
    switch (parentClass.rotation) {
        case Rotation::NO_ROTATION: {
            angle = 0;
            break;
        }
        case Rotation::CLOCKWISE: {
            angle = -PI / 2;
            break;
        }
        case Rotation::COUNTER_CLOCKWISE: {
            angle = PI / 2;
            break;
        }
        case Rotation::HALF_CIRCLE: {
            angle = PI;
            break;
        }
    }

    cornerVector = Vector2Rotate(cornerVector, angle);

    DrawRectangle(position.x, position.y, cornerVector.x, cornerVector.y,
                  parentClass.backgroundColor);
    DrawRectangleLines(position.x, position.y, cornerVector.x, cornerVector.y,
                       parentClass.borderColor);
    Vector2 center = Vector2Add(
        position, Vector2Scale({parentClass.width, parentClass.height}, 0.5));
    TextUtility::renderText(data, center, TextUtility::fontInter,
                        parentClass.borderColor, TextUtility::NORMAL_SIZE,
                        TextUtility::SPACING);
    if (nextNode != nullptr) {
        Vector2 beginPosition = getEndPoint();
        Vector2 endPosition = nextNode->getStartPoint();
        DrawLineEx(beginPosition, endPosition, 3, parentClass.borderColor);
        nextNode->render();
    }
}

Vector2 SinglyLinkedList::Node::getStartPoint() const {
    switch (parentClass.rotation) {
        case Rotation::NO_ROTATION: {
            return Vector2Add(position, Vector2{0, parentClass.height / 2});
        }
        case Rotation::CLOCKWISE: {
            return Vector2Add(position, Vector2{-parentClass.height / 2, 0});
        }
        case Rotation::COUNTER_CLOCKWISE: {
            return Vector2Add(position, Vector2{parentClass.height / 2, 0});
        }
        case Rotation::HALF_CIRCLE: {
            return Vector2Add(position, Vector2{0, -parentClass.height / 2});
        }
    }
}

Vector2 SinglyLinkedList::Node::getEndPoint() const {
    switch (parentClass.rotation) {
        case Rotation::NO_ROTATION: {
            return Vector2Add(getStartPoint(), Vector2{parentClass.width, 0});
        }

        case Rotation::COUNTER_CLOCKWISE: {
            return Vector2Add(getStartPoint(), Vector2{0, -parentClass.width});
        }

        case Rotation::CLOCKWISE: {
            return Vector2Add(getStartPoint(), Vector2{0, parentClass.width});
        }

        case Rotation::HALF_CIRCLE: {
            return Vector2Add(getStartPoint(), Vector2{-parentClass.width, 0});
        }
    }
}

void SinglyLinkedList::setColor(Color border, Color background,
                                Color highlight) {
    borderColor = border;
    backgroundColor = background;
    highlightColor = highlight;
}

void SinglyLinkedList::addNode(int data) { addNode(std::to_string(data)); }
void SinglyLinkedList::addNode(std::string data) {
    countNode++;
    Node* curr = root;
    if (curr != nullptr) {
        while (curr->nextNode != nullptr) curr = curr->nextNode;
        Vector2 nextNodePosition = curr->getPosition();
        switch (rotation) {
            case Rotation::NO_ROTATION: {
                nextNodePosition =
                    Vector2Add(nextNodePosition, Vector2{width + distance, 0});
                break;
            }
            case Rotation::CLOCKWISE: {
                nextNodePosition =
                    Vector2Add(nextNodePosition, Vector2{0, width + distance});
                break;
            }
            case Rotation::COUNTER_CLOCKWISE: {
                nextNodePosition =
                    Vector2Add(nextNodePosition, Vector2{0, -width - distance});
                break;
            }
            case Rotation::HALF_CIRCLE: {
                nextNodePosition =
                    Vector2Add(nextNodePosition, Vector2{-width - distance, 0});
                break;
            }
        }
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