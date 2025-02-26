#include "singlyLinkedList.h"
void Node::render() {
    DrawCircle(position.x, position.y, radius, borderColor.getCurrentColor());
}