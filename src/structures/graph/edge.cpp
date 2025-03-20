#include "graph/edge.h"

const Color GraphEdge::NORMAL_COLOR = WHITE;
const Color GraphEdge::HIGHLIGHT_COLOR = GOLD;
const Color GraphEdge::TEXT_COLOR = GOLD;
const int GraphEdge::THICKNESS = 2;
void GraphEdge::update() {
    Vector2 newPosition =
        Vector2Add(node1->getPosition(), node2->getPosition());
    newPosition = Vector2Scale(newPosition, 0.5f);
    setPosition(newPosition);
    color.update();
}

void GraphEdge::render() {
    DrawUtility::drawEdge(node1->getPosition(), node2->getPosition(), color.getCurrentColor());
    DrawUtility::drawText(std::to_string(weight), position, DrawUtility::inter20, TEXT_COLOR, DrawUtility::NORMAL_SIZE, DrawUtility::SPACING, VerticalAlignment::TOP, HorizontalAlignment::LEFT);
}

void GraphEdge::highlight(bool isImmediate) {
    color.setBaseColor(color.getCurrentColor());
    color.setTargetColor(HIGHLIGHT_COLOR);   
    color.setFactor(float(isImmediate));
}

void GraphEdge::deHighlight(bool isImmediate) {
    color.setBaseColor(color.getCurrentColor());
    color.setTargetColor(NORMAL_COLOR);
    color.setFactor(float(isImmediate));
}

void GraphEdge::makeTransparent(bool isImmediate) {
    Color current = color.getCurrentColor();
    color.setBaseColor(current);
    current.a = 0;
    color.setTargetColor(current);
    color.setFactor(float(isImmediate));
}

void GraphEdge::makeOpaque(bool isImmediate) {
    Color current = color.getCurrentColor();
    color.setBaseColor(current);
    current.a = 255;
    color.setTargetColor(current);
    color.setFactor(float(isImmediate));

}

bool GraphEdge::isCompleted() {
    return color.isCompleted();
}

float GraphEdge::getLength() {
    return Vector2Distance(node1->getPosition(), node2->getPosition());
}

int GraphEdge::getWeight() {
    return weight;
}
