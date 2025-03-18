#include "node.h"

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