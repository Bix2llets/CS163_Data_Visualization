#include "SLLNode.h"
void Node::render() {
    DrawCircle(position.x, position.y, radius, borderColor.getCurrentColor());
    DrawCircleV(position, radius - 3, PALETTE.backgroundNormal);

    DrawUtility::drawText(data, position, DrawUtility::inter20,
                          DrawUtility::TEXT_COLOR, DrawUtility::NORMAL_SIZE,
                          DrawUtility::SPACING, VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
}

Node::Node(std::string data, float x, float y, int radius, ColorSet palette,
           float animationRate)
    : data{data},
      Animation{x, y, animationRate},
      animationRate{animationRate},
      PALETTE{palette},
      radius{radius},
      borderColor{PALETTE.borderHighlight, PALETTE.borderNormal, animationRate},
      edgeColor{PALETTE.borderHighlight, PALETTE.borderNormal},
      nextNode{nullptr} {};

Node::Node(int data, float x, float y, int radius, ColorSet palette,
           float animationRate)
    : Node(std::to_string(data), x, y, radius, palette, animationRate) {};

void Node::update() {
    Animation::update();
    borderColor.update();
    edgeColor.update();
}

void Node::setAnimationRate(float rate) {
    animationRate = rate;
    borderColor.setUpdateRate(rate);
    edgeColor.setUpdateRate(rate);
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