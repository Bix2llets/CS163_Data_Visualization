#include "SLLScene.h"

float SLLScene::stepDelay = 0.f;
float SLLScene::timeLeft = 0.f;

const Rectangle SLLScene::CANVAS = {50, 50, 1500, 550};
float SLLScene::animationRate = 1.0f;
SLL SLLScene::sll(CANVAS, animationRate);
std::deque<SLL> SLLScene::steps;
void SLLScene::setSpecs(float _stepDelay, float _animationRate) {
    stepDelay = _stepDelay;
    animationRate = _animationRate;
    sll.setAnimationRate(animationRate);
}
void SLLScene::addEnd(std::string data) {
    addStep();
    SLL &curr = steps.back();
    curr.addEnd(data);
};
void SLLScene::addAt(std::string data, int place) {
    if (steps.size()) {
        if (place > steps.back().nodeCount + 1) return;
    } else {
        if (place > sll.nodeCount + 1) return;
    }
    addStep();
    steps.back().shiftForward(place);
    addStep();
    steps.back().addAt(data, place);
    std::cerr << steps.back().nodeCount << "\n";
};
void SLLScene::removeEnd() {
    addStep();
    SLL &curr = steps.back();
    curr.removeEnd();
};
void SLLScene::removeAt(int place) {
    std::cerr << "Begin remove at\n";
    if (steps.size()) {
        std::cerr << "Checking: " << place << steps.back().nodeCount << "\n";
        if (place > steps.back().nodeCount) {
            std::cerr << "Exitted due to invalid place\n";
            return;
        }
    } else {
        if (place > sll.nodeCount) {
            std::cerr << place << " " << sll.nodeCount << "\n";
            std::cerr << "Exitted due to invalid place\n";
            return;
        }
    }
    addStep();
    steps.back().removeAt(place);
    addStep();
    steps.back().shiftBackward(place);
};
void SLLScene::update() {
    sll.update();
    if (!sll.isFinished()) return;

    timeLeft -= GetFrameTime();
    if (abs(timeLeft) < 1e-6) timeLeft = 0;
    if (timeLeft <= 0) timeLeft = 0;

    if (timeLeft == 0 && steps.size()) {
        sll = steps.front();
        steps.pop_front();
        timeLeft = stepDelay;
    }
};
void SLLScene::addStep() {
    if (steps.size())
        steps.push_back(steps.back().clone());
    else
        steps.push_back(sll.clone());
    steps.back().finishAnimation();
}

void SLLScene::render() { sll.render(); }