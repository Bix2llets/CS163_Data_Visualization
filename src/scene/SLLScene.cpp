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
    std::cerr << "Done adding\n";
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
    std::cerr << "Done adding\n";
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
            std::cerr << "Exitted due to invalid place\n";
            return;
        }
    }
    std::cerr << place << " " << steps.back().nodeCount << "\n";
    addStep();
    steps.back().removeAt(place);
    addStep();
    steps.back().shiftBackward(place);
};
void SLLScene::update() {
    sll.update();
    // std::cerr << "Done sll updating\n";
    if (!sll.isFinished()) return;

    timeLeft -= GetFrameTime();
    if (abs(timeLeft) < 1e-6) timeLeft = 0;
    if (timeLeft <= 0) timeLeft = 0;

    if (timeLeft == 0 && steps.size()) {
        std::cerr << "Next step init\n" << " " << steps.size() << " ";
        sll = steps.front();
        steps.pop_front();
        std::cerr << steps.size() << "\n";
        timeLeft = stepDelay;
    }
    // std::cerr << "Done scene updating\n";
};
void SLLScene::addStep() {
    std::cerr << "addStep called\n";
    if (steps.size())
        steps.push_back(steps.back().clone());
    else
        steps.push_back(sll.clone());
    steps.back().finishAnimation();
    // std::cerr << "Done adding copy to end of steps deque\n";
}

void SLLScene::render() { sll.render(); }