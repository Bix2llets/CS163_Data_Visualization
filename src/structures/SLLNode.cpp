#include "SLLNode.h"
void Node::render() {
    DrawCircle(position.x, position.y, radius, borderColor.getCurrentColor());
    DrawCircleV(position, radius - 3, PALETTE.backgroundNormal);

    DrawUtility::drawText(data, position, DrawUtility::inter20,
                          PALETTE.textNormal, DrawUtility::NORMAL_SIZE,
                          DrawUtility::SPACING, VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
}

Node::Node(std::string data, float x, float y, int radius, ColorSet palette,
           float animationRate)
    : data{data},
      Animation{x, y},
      PALETTE{palette},
      radius{radius},
      borderColor{PALETTE.borderNormal, PALETTE.borderNormal, animationRate},
      edgeColor{PALETTE.borderHighlight, PALETTE.borderNormal, animationRate},
      nextNode{nullptr} {};

Node::Node(int data, float x, float y, int radius, ColorSet palette,
           float animationRate)
    : Node(std::to_string(data), x, y, radius, palette, animationRate) {};

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
