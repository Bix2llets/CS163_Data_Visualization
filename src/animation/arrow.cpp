#include "arrow.h"

void AnimationEdge::render() {
    Vector2 beginPos = beginPosition.getPosition();
    Vector2 endPos = endPosition.getPosition();

    Color drawColor = isHighlighted ? highlightColor : normalColor;
    // For the arrow tip
    DrawUtility::drawEdge(beginPos, endPos, drawColor);
}
void AnimationEdge::update() {
    beginPosition.update();
    endPosition.update();
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
};
void AnimationEdge::setVelocity(float velo) {
    beginPosition.setVelocity(velo);
    endPosition.setVelocity(velo);
};
bool AnimationEdge::isCompleted() {
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