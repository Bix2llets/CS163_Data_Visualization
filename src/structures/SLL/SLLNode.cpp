#include "SLL/SLLNode.h"

ColorSet const *Node::PALETTE = &nodeColorSet;
void Node::render() {
    DrawCircle(position.x, position.y, radius, borderColor.getCurrentColor());
    DrawCircleV(position, radius - 3, PALETTE->backgroundNormal);

    Utility::drawText(data, position, Utility::inter20,
                          PALETTE->textNormal, Utility::NORMAL_SIZE,
                          Utility::SPACING, VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
}

Node::Node(std::string data, float x, float y, int radius)
    : data{data},
      Animation{x, y},
      radius{radius},
      borderColor{&PALETTE->borderNormal, &PALETTE->borderNormal},
      edgeColor{&PALETTE->borderNormal, &PALETTE->borderNormal},
      nextNode{nullptr} {};

Node::Node(int data, float x, float y, int radius)
    : Node(std::to_string(data), x, y, radius) {};

void Node::update() {
    Animation::update();
    borderColor.update();
    edgeColor.update();
}

bool Node::isFinished() {
    return this->isCompleted() && borderColor.isCompleted() &&
           edgeColor.isCompleted();
}

void Node::finishAnimation() {
    Animation::makeFinish();
    borderColor.makeFinish();
    edgeColor.makeFinish();
}

void Node::updateAnimation() {
    Animation::update();
}
