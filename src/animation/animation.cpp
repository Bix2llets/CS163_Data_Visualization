#include "animation.h"

float Animation::rate = 1.0f;
double Animation::bezier(double t) {
    std::pair<double,double> A(0.0, 0.0);
    std::pair<double,double> B(0.42, 0.0);
    std::pair<double,double> C(0.58, 1.0);
    std::pair<double,double> D(1.0, 1.0);
    double tA = -t*t*t + 3*t*t - 3*t + 1;
    double tB = 3*t*t*t - 6*t*t + 3*t;
    double tC = -3*t*t*t + 3*t*t;
    double tD = t*t*t;
    double rY = A.second * tA + B.second * tB + C.second * tC + D.second * tD;
    return rY;
}

#include <iostream>

bool Animation::displace(double currTime, double TRANS_TIME) {
    if (Vector2Distance(position, targetedPosition) < 1e-6) {
        position = targetedPosition;
        return true;
    }
    if (currTime >= TRANS_TIME) {
        position = targetedPosition;
        return true;
    }
    double Sx = position.x, Sy = position.y;
    double Dx = targetedPosition.x, Dy = targetedPosition.y;
    double Ux = Dx - Sx;
    double Uy = Dy - Sy;
    double leng = sqrt(Ux*Ux + Uy*Uy);
    double distance = leng * bezier(std::min((double)TRANS_TIME, currTime) / TRANS_TIME);
    position = (Vector2){Sx + Ux / leng * distance, Sy + Uy / leng * distance};
    return false;
}

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

Vector2 Animation::getPosition() { return position; }

void Animation::setPosition(Vector2 newPosition) { position = newPosition; }

void Animation::makeFinish() {
    position = targetedPosition;
}

bool Animation::fadeEffect(double currentTime, double TRANS_TIME) {
    if (currentTime >= TRANS_TIME) {
        std::cout << "passed\n";
        this->alpha = 255.f;
        return true;
    }
    float halfTime = TRANS_TIME / 2;
    if (currentTime <= halfTime) this->alpha = 255.f - (currentTime / halfTime) * 255.f;
    else this->alpha = (currentTime - halfTime) / halfTime * 255.f;
    return false;
}