#include "graph/node.h"

const ColorSet GraphNode::PALETTE = {BLACK, GOLD, WHITE, GOLD, BLACK, GOLD};
const int GraphNode::RADIUS = 25;
const int GraphNode::BORDER_WIDTH = 2;

const float GraphNode::MASS = 1;
void GraphNode::render() {
    DrawCircle(position.x, position.y, RADIUS, borderColor.getCurrentColor());
    // std::cerr << position.x << " " << position.y << "\n";
    DrawCircle(position.x, position.y, RADIUS - BORDER_WIDTH,
               PALETTE.backgroundNormal);

    DrawUtility::drawText(std::to_string(label), position, DrawUtility::inter20,
                          PALETTE.textNormal, DrawUtility::NORMAL_SIZE,
                          DrawUtility::SPACING, VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
}

void GraphNode::update() {
    borderColor.update();

    // * Motion update
    Vector2 displacement = Vector2Scale(velocity, Loop::DELTA_TIME);
    position = Vector2Add(position, displacement);
    velocity = Vector2Scale(velocity, 0.90f);

    if (position.x < Loop::UPPER_LEFT.x + RADIUS) {
        position.x = Loop::UPPER_LEFT.x + RADIUS;
        velocity.x = -velocity.x * 0.2f;
    }
    if (position.x > Loop::LOWER_RIGHT.x - RADIUS) {
        position.x = Loop::LOWER_RIGHT.x - RADIUS;
        velocity.x = -velocity.x * 0.2f;
    }
    if (position.y < Loop::UPPER_LEFT.y + RADIUS) {
        position.y = Loop::UPPER_LEFT.y + RADIUS;
        velocity.y = -velocity.y * 0.2f;
    }
    if (position.y > Loop::LOWER_RIGHT.y - RADIUS) {
        position.y = Loop::LOWER_RIGHT.y - RADIUS;
        velocity.y = -velocity.y * 0.2f;
    }
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

void GraphNode::finishAnimation() { borderColor.setFactor(1.0f); }
void GraphNode::highlight(bool isImmediate) {
    borderColor.setBaseColor(borderColor.getCurrentColor());
    borderColor.setTargetColor(PALETTE.borderHighlight);
    borderColor.setFactor(float(isImmediate));
}

void GraphNode::deHighlight(bool isImmediate) {
    borderColor.setBaseColor(borderColor.getCurrentColor());
    borderColor.setTargetColor(PALETTE.borderNormal);
    borderColor.setFactor(float(isImmediate));
}

void GraphNode::setVelocity(Vector2 newVelocity) { velocity = newVelocity; }

void GraphNode::applyForce(Vector2 force) {
    Vector2 acceleration = Vector2Scale(force, 1.0f / MASS);
    Vector2 deltaVelocity = Vector2Scale(acceleration, Loop::DELTA_TIME);

    velocity = Vector2Add(velocity, deltaVelocity);
    velocity = Vector2ClampValue(velocity, -240.f, 240.f);
}

int GraphNode::getLabel() { return label; }

bool GraphNode::isCompleted() { return borderColor.isCompleted(); }

bool GraphNode::isConnected(std::shared_ptr<GraphNode> node) {
    for (auto existedNode: adjacentList) 
        if (existedNode.dest == node) return false;
    return true;
}

AnimationColor &GraphNode::getBorderColor() {
    return borderColor;
}