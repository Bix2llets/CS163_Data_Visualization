#include "graph/node.h"

const int GraphNode::RADIUS = 25;
const int GraphNode::BORDER_WIDTH = 4;
ColorSet const *GraphNode::PALETTE  = &nodeColorSet;

Color const *GraphNode::HOVER = &GBLight::LIGHT_GREEN;
const float GraphNode::MASS = 1.f;

void GraphNode::render() {
    Color border = borderColor.getCurrentColor();
    if (dragged) border = *HOVER;
    DrawCircle(position.x, position.y, RADIUS, border);
    // std::cerr << position.x << " " << position.y << "\n";
    Color backgroundColor = PALETTE->backgroundNormal;
    backgroundColor.a = border.a;
    DrawCircle(position.x, position.y, RADIUS - BORDER_WIDTH, backgroundColor);

    Color textColor = PALETTE->textNormal;
    textColor.a = border.a;
    Utility::drawText(std::to_string(label), position, Utility::inter20,
                          textColor, Utility::NORMAL_SIZE,
                          Utility::SPACING, VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
}

void GraphNode::update() {
    borderColor.update();

    // * Motion update
    if (!dragged) {
        Vector2 displacement = Vector2Scale(velocity, AppInfo::DELTA_TIME);
        position = Vector2Add(position, displacement);
        velocity = Vector2Scale(velocity, 0.90f);
    }

    if (position.x < AppInfo::UPPER_LEFT.x + RADIUS) {
        position.x = AppInfo::UPPER_LEFT.x + RADIUS;
        velocity.x = -velocity.x * 0.2f;
    }
    if (position.x > AppInfo::LOWER_RIGHT.x - RADIUS) {
        position.x = AppInfo::LOWER_RIGHT.x - RADIUS;
        velocity.x = -velocity.x * 0.2f;
    }
    if (position.y < AppInfo::UPPER_LEFT.y + RADIUS) {
        position.y = AppInfo::UPPER_LEFT.y + RADIUS;
        velocity.y = -velocity.y * 0.2f;
    }
    if (position.y > AppInfo::LOWER_RIGHT.y - RADIUS) {
        position.y = AppInfo::LOWER_RIGHT.y - RADIUS;
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
    isHighlighted = true;
    borderColor.transitionToward(&PALETTE->borderHighlight);
    borderColor.setFactor(float(isImmediate));
}

void GraphNode::deHighlight(bool isImmediate) {
    isHighlighted = false;
    borderColor.transitionToward(&PALETTE->borderNormal);
    borderColor.setFactor(float(isImmediate));
}

void GraphNode::setVelocity(Vector2 newVelocity) { velocity = newVelocity; }

void GraphNode::applyForce(Vector2 force) {
    Vector2 acceleration = Vector2Scale(force, 1.0f / MASS);
    Vector2 deltaVelocity = Vector2Scale(acceleration, AppInfo::DELTA_TIME);

    velocity = Vector2Add(velocity, deltaVelocity);
    // velocity = Vector2ClampValue(velocity, -2400.f / 10, 2400.f / 10);
}

int GraphNode::getLabel() { return label; }

bool GraphNode::isCompleted() { return borderColor.isCompleted(); }

bool GraphNode::isConnected(std::shared_ptr<GraphNode> node) {
    for (auto existedNode : adjacentList)
        if (existedNode.dest == node) return false;
    return true;
}

void GraphNode::makeOpaque(bool isImmediate) {
    Color target = borderColor.getTargetColor();
    isOpaque = true;
    target.a = 255;

    borderColor.AnimationColor::setTargetColor(target);
    borderColor.setFactor(float(isImmediate));
}

void GraphNode::makeTransparent(bool isImmediate) {
    isOpaque = false;
    Color target = borderColor.getTargetColor();

    target.a = 0;

    borderColor.AnimationColor::setTargetColor(target);
    borderColor.setFactor(float(isImmediate));
}

bool GraphNode::getOpaque() { return isOpaque; }

bool GraphNode::getHighlighted() { return isHighlighted; }