#include "arrow.h"

AnimationEdge::AnimationEdge(Vector2 beginPos, Vector2 endPos, AnimationColor currentColor, float newFac)
: beginPosition{beginPos.x, beginPos.y, newFac},
  endPosition{endPos.x, endPos.y, newFac},
  isHighlighted{false}, currentColor{currentColor} { currentColor.setUpdateRate(newFac);};

void AnimationEdge::render() {
    Vector2 beginPos = beginPosition.getPosition();
    Vector2 endPos = endPosition.getPosition();

    
    // For the arrow tip
    DrawUtility::drawEdge(beginPos, endPos, currentColor.getCurrentColor());
}
void AnimationEdge::update() {
    updateMotion();
    updateColor();
}

void AnimationEdge::updateMotion() {
    beginPosition.update();
    endPosition.update();
}

void AnimationEdge::updateColor() {
    currentColor.update();
}
void AnimationEdge::setMotionBeginPosition(Vector2 target) {
    beginPosition.setTargetedPosition(target);
};
void AnimationEdge::setMotionEndPosition(Vector2 target) {
    endPosition.setTargetedPosition(target);
};
void AnimationEdge::setBeginPosition(Vector2 target) {
    beginPosition.setPosition(target);
};
void AnimationEdge::setEndPosition(Vector2 target) {
    endPosition.setPosition(target);
};
void AnimationEdge::setColor(AnimationColor newColor) {
    currentColor = newColor;
};
void AnimationEdge::setUpdateRate(float rate) {
    beginPosition.setUpdateRate(rate);
    endPosition.setUpdateRate(rate);
    currentColor.setUpdateRate(rate);
}
bool AnimationEdge::isMotionCompleted() {
    return beginPosition.isCompleted() && endPosition.isCompleted();
};
bool AnimationEdge::isColorCompleted() {
    return currentColor.isCompleted();
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

void AnimationEdge::makeFinish() {
    currentColor.makeFinish();
    endPosition.setPosition(endPosition.getTargetedPosition());
    beginPosition.setPosition(beginPosition.getTargetedPosition());
}

void AnimationEdge::setBaseColor(Color color) {currentColor.setBaseColor(color);}
void AnimationEdge::setTargetColor(Color color) {currentColor.setTargetColor(color);}
void AnimationEdge::setFactor(float factor) {currentColor.setFactor(factor);}