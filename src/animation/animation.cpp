#include "animation.h"

void Animation::update() {
    if (Vector2Distance(position, targetedPosition) == 0) return;
    Vector2 displacement = Vector2Subtract(targetedPosition, position);
    displacement =
        Vector2Scale(displacement, 1.0f / Vector2Length(displacement));
    // std::cerr << position.x << " " << position.y << "\n";
    // std::cerr << targetedPosition.x << " " << targetedPosition.y << "\n";
    displacement = Vector2Scale(
        displacement, rate);
    if (abs(displacement.x) < 1e-6) displacement.x = 0;
    if (abs(displacement.y) < 1e-6) displacement.y = 0;
    // std::cerr << displacement.x << " " << displacement.y << " " << rate << "\n";
    if (Vector2Length(displacement) >=
        Vector2Distance(position, targetedPosition))
        position = targetedPosition;
    else
        position =
            Vector2Add(position, displacement);
    // std::cerr << "Result: " << position.x << " " << position.y << "\n----\n";
}

void Animation::setTargetedPosition(Vector2 target) {
    targetedPosition = target;
}   

bool Animation::isCompleted() const {
    return (Vector2Distance(position, targetedPosition) < 1e-6);
}

void Animation::render() {
    DrawCircle(position.x, position.y, 50, BLACK);
}

void Animation::setUpdateRate(float newRate) {
    rate = newRate;
}

Vector2 Animation::getTargetedPosition() { return targetedPosition; }