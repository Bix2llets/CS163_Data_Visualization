#include "arrow.h"
void AnimationEdge::render() {
    Vector2 beginPos = beginPosition.getPosition();
    Vector2 endPos = endPosition.getPosition();

    
    // For the arrow tip
    DrawUtility::drawEdge(beginPos, endPos, currentColor.getCurrentColor());
}
void AnimationEdge::update() {
    beginPosition.update();
    endPosition.update();
    currentColor.update();
}
void AnimationEdge::setAnimationBeginPosition(Vector2 target) {
    beginPosition.setTargetedPosition(target);
};
void AnimationEdge::setAnimationEndPosition(Vector2 target) {
    endPosition.setTargetedPosition(target);
};
void AnimationEdge::setBeginPosition(Vector2 target) {
    beginPosition.setPosition(target);
};
void AnimationEdge::setEndPosition(Vector2 target) {
    endPosition.setPosition(target);
};
void AnimationEdge::setHighlight(bool highlight) {
    isHighlighted = highlight;
    currentColor.setFactor(0);
    if (isHighlighted) {
        currentColor.setBaseColor(DrawUtility::EDGE_NORMAL);
        currentColor.setTargetColor(DrawUtility::EDGE_HIGHLIGHTED);
    }
    else {
        currentColor.setBaseColor(DrawUtility::EDGE_HIGHLIGHTED);
        currentColor.setTargetColor(DrawUtility::EDGE_NORMAL);
    }
};
void AnimationEdge::setVelocity(float velo) {
    beginPosition.setVelocity(velo);
    endPosition.setVelocity(velo);
};
bool AnimationEdge::isMotionCompleted() {
    return beginPosition.isCompleted() && endPosition.isCompleted();
};
bool AnimationEdge::isColorCompleted() {
    return beginPosition.isCompleted() && endPosition.isCompleted();
};

Vector2 AnimationEdge::getBeginPosition() {
    return beginPosition.getPosition();
}
Vector2 AnimationEdge::getEndPosition() { return endPosition.getPosition(); }
Vector2 AnimationEdge::getTargetedBeginPosition() {
    return beginPosition.getTargetedPosition();
}
Vector2 AnimationEdge::getTargetedEndPosition() {
    return endPosition.getTargetedPosition();
}