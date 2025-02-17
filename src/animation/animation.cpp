#include "animation.h"

void Animation::update() {
    if (Vector2Distance(position, targetedPosition) == 0) return;
    Vector2 displacement = Vector2Subtract(targetedPosition, position);
    displacement =
        Vector2Scale(displacement, 1.0f / Vector2Length(displacement));
    std::cerr << position.x << " " << position.y << "\n";
    std::cerr << targetedPosition.x << " " << targetedPosition.y << "\n";
    displacement = Vector2Scale(
        displacement, BASE_VELOCITY * velocityCoefficient);
    std::cerr << displacement.x << " " << displacement.y << "\n";
    if (Vector2Length(displacement) >=
        Vector2Distance(position, targetedPosition))
        position = targetedPosition;
    else
        position =
            Vector2Add(position, displacement);
    std::cerr << "Result: " << position.x << " " << position.y << "\n----\n";
}

void Animation::setTargetedPosition(Vector2 target) {
    targetedPosition = target;
}   

bool Animation::isCompleted() const {
    return (Vector2Distance(position, targetedPosition) == 0);
}

void Animation::render() {
    DrawCircle(position.x, position.y, 50, BLACK);
}