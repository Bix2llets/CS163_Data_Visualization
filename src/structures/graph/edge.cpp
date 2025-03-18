#include "edge.h"

const int GraphEdge::THICKNESS = 2;
void GraphEdge::update() {
    Vector2 newPosition =
        Vector2Add(node1->getPosition(), node2->getPosition());
    newPosition = Vector2Scale(newPosition, 0.5f);
    setPosition(newPosition);
}

void GraphEdge::render() {
    DrawUtility::drawEdge(node1->getPosition(), node2->getPosition(), color.getCurrentColor());
    DrawUtility::drawText(std::to_string(weight), position, DrawUtility::inter20, TEXT_COLOR, DrawUtility::NORMAL_SIZE, DrawUtility::SPACING, VerticalAlignment::TOP, HorizontalAlignment::LEFT);
}

void GraphEdge::highlight() {
    color.setBaseColor(color.getCurrentColor());
    color.setTargetColor(HIGHLIGHT_COLOR);   
}

void GraphEdge::deHighlight() {
    color.setBaseColor(color.getCurrentColor());
    color.setTargetColor(NORMAL_COLOR);
}

void GraphEdge::makeTransparent() {
    Color current = color.getCurrentColor();
    color.setBaseColor(current);
    current.a = 0;
    color.setTargetColor(current);
}

void GraphEdge::makeOpaque() {
    Color current = color.getCurrentColor();
    color.setBaseColor(current);
    current.a = 255;
    color.setTargetColor(current);

}