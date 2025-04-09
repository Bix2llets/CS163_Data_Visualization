#include "graph/edge.h"

const Color* GraphEdge::NORMAL_COLOR = &nodeColorSet.borderNormal;
const Color* GraphEdge::HIGHLIGHT_COLOR = &nodeColorSet.borderHighlight;
const Color* GraphEdge::TEXT_COLOR = &nodeColorSet.textNormal;
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
    Color textColor = *TEXT_COLOR;
    Color backTextColor = nodeColorSet.backgroundNormal;
    textColor.a = color.getCurrentColor().a;
    backTextColor.a = 180 * color.getCurrentColor().a / 255;
    Vector2 textDimension = MeasureTextEx(DrawUtility::inter20, std::to_string(weight).c_str(), 16, DrawUtility::SPACING);
    textDimension.x += 10;
    textDimension.y += 10;
    DrawRectangle(position.x - textDimension.x / 2, position.y - textDimension.y / 2, textDimension.x, textDimension.y, backTextColor);
    DrawUtility::drawText(std::to_string(weight), position,
                          DrawUtility::inter16, textColor,
                          16, DrawUtility::SPACING,
                          VerticalAlignment::CENTERED, HorizontalAlignment::CENTERED);
}
void GraphEdge::highlight(bool isImmediate) {
    isHighlighted = true;
    color.transitionToward(HIGHLIGHT_COLOR);
    color.setFactor(float(isImmediate));
}

void GraphEdge::deHighlight(bool isImmediate) {
    isHighlighted = false;
    color.transitionToward(NORMAL_COLOR);
    color.setFactor(float(isImmediate));
}

void GraphEdge::makeTransparent(bool isImmediate) {
    isOpaque = false;
    Color target = color.getTargetColor();
    target.a = 0;
    color.AnimationColor::transitionToward(target);
    color.setFactor(float(isImmediate));
}

void GraphEdge::makeOpaque(bool isImmediate) {
    isOpaque = true;

    Color target = color.getTargetColor();
    target.a = 255;
    color.AnimationColor::transitionToward(target);
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