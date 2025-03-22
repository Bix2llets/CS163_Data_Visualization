#include "graph/edge.h"

const Color GraphEdge::NORMAL_COLOR = Color{59, 66, 82, 255};
const Color GraphEdge::HIGHLIGHT_COLOR = Color{229, 189, 80, 255};
const Color GraphEdge::TEXT_COLOR = Color{186, 180, 163, 255};
const int GraphEdge::THICKNESS = 2;
void GraphEdge::update() {
    Vector2 newPosition =
        Vector2Add(node1->getPosition(), node2->getPosition());
    newPosition = Vector2Scale(newPosition, 0.5f);
    setPosition(newPosition);
    color.update();
}

void GraphEdge::render() {
    DrawUtility::drawEdge(node1->getPosition(), node2->getPosition(),
                          color.getCurrentColor());
}
void GraphEdge::renderText() {
    Color textColor = TEXT_COLOR;
    textColor.a = color.getCurrentColor().a;
    DrawUtility::drawText(std::to_string(weight), position,
                          DrawUtility::inter20, textColor,
                          16, DrawUtility::SPACING,
                          VerticalAlignment::TOP, HorizontalAlignment::LEFT);
}
void GraphEdge::highlight(bool isImmediate) {
    isHighlighted = true;
    color.setBaseColor(color.getCurrentColor());
    color.setTargetColor({HIGHLIGHT_COLOR.r, HIGHLIGHT_COLOR.g, HIGHLIGHT_COLOR.b, color.getTargetColor().a});
    color.setFactor(float(isImmediate));
}

void GraphEdge::deHighlight(bool isImmediate) {
    isHighlighted = false;
    color.setBaseColor(color.getCurrentColor());
    color.setTargetColor({NORMAL_COLOR.r, NORMAL_COLOR.g, NORMAL_COLOR.b, color.getTargetColor().a});
    color.setFactor(float(isImmediate));
}

void GraphEdge::makeTransparent(bool isImmediate) {
    isOpaque = false;
    Color current = color.getCurrentColor();
    Color target = color.getTargetColor();
    target.a = 0;
    color.setBaseColor(current);
    color.setTargetColor(target);
    color.setFactor(float(isImmediate));
}

void GraphEdge::makeOpaque(bool isImmediate) {
    isOpaque = true;
    Color current = color.getCurrentColor();

    Color target = color.getTargetColor();
    target.a = 255;
    color.setBaseColor(current);
    color.setTargetColor(target);
    color.setFactor(float(isImmediate));
}

bool GraphEdge::isCompleted() { return color.isCompleted(); }

float GraphEdge::getLength() {
    return Vector2Distance(node1->getPosition(), node2->getPosition());
}

int GraphEdge::getWeight() { return weight; }

void GraphEdge::finishAnimation() { color.setFactor(1.0f); }

bool GraphEdge::getOpaque() {
    return isOpaque;
}

bool GraphEdge::getHighlighted() {
    return isHighlighted;
}