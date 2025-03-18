#include "node.h"

const ColorSet GraphNode::PALETTE = DEF_SET;
const int GraphNode::RADIUS = 30;
const int GraphNode::BORDER_WIDTH = 2;

const float GraphNode::MASS = 1;
void GraphNode::render() {
    DrawCircle(position.x, position.y, RADIUS, borderColor.getCurrentColor());

    DrawCircle(position.x, position.y, RADIUS - BORDER_WIDTH, PALETTE.backgroundNormal);

    DrawUtility::drawText(std::to_string(label), position, DrawUtility::inter20, PALETTE.textNormal, DrawUtility::NORMAL_SIZE, DrawUtility::SPACING, VerticalAlignment::CENTERED, HorizontalAlignment::CENTERED);
}

void GraphNode::update() {
    borderColor.update();
}

void GraphNode::addEdge(std::shared_ptr<GraphNode> dest, int weight) {
    adjacentList.push_back({dest, weight});
}

void GraphNode::removeEdge(std::shared_ptr<GraphNode> dest) {
    for (int i = 0; i < adjacentList.size(); i++) {
        OutgoingEdge edge = adjacentList[i];
        if (edge.dest == dest) {
            adjacentList.erase(adjacentList.begin() + i);
            i--;
        }
    }
}

void GraphNode::finishAnimation() {
    borderColor.setFactor(1.0f);
}
void GraphNode::highlight() {
    borderColor.setBaseColor(borderColor.getCurrentColor());
    borderColor.setTargetColor(PALETTE.borderHighlight);
    borderColor.setFactor(0.f);
}

void GraphNode::deHighlight() {
    borderColor.setBaseColor(borderColor.getCurrentColor());
    borderColor.setTargetColor(PALETTE.borderNormal);
    borderColor.setFactor(0.f);
}

void GraphNode::setVelocity(Vector2 newVelocity) {
    velocity  = newVelocity;
}

void GraphNode::applyForce(Vector2 force) {
    Vector2 acceleration = Vector2Scale(force, 1.0f / MASS);
    Vector2 deltaVelocity = Vector2Scale(acceleration, Loop::DELTA_TIME);

    velocity = Vector2Add(velocity, deltaVelocity);
}