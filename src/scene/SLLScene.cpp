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
    steps.back().highlightTo(steps.back().nodeCount - 1);
    addStep();
    steps.back().addEnd(data);
};
void SLLScene::addAt(std::string data, int place) {
    if (steps.size()) {
        if (place > steps.back().nodeCount + 1) return;
    } else {
        if (place > sll.nodeCount + 1) return;
    }
    place--;
    addStep();
    steps.back().deHighlight();
    steps.back().highlightTo(place - 1);
    addStep();
    steps.back().shiftForward(place);
    addStep();
    steps.back().addAt(data, place);
    std::cerr << steps.back().nodeCount << "\n";
};
void SLLScene::removeEnd() {
    addStep();
    steps.back().deHighlight();
    steps.back().highlightTo(steps.back().nodeCount - 1);
    addStep();
    steps.back().moveOutEnd();
    addStep();
    steps.back().removeEnd();
};
void SLLScene::removeAt(int place) {
    std::cerr << "Begin remove at\n";
    place--;
    if (steps.size()) {
        std::cerr << "Checking: " << place << steps.back().nodeCount << "\n";
        if (place >= steps.back().nodeCount) {
            std::cerr << "Exitted due to invalid place\n";
            return;
        }
    } else {
        if (place >= sll.nodeCount) {
            std::cerr << place << " " << sll.nodeCount << "\n";
            std::cerr << "Exitted due to invalid place\n";
            return;
        }
    }
    addStep();
    steps.back().deHighlight();
    steps.back().highlightTo(place);
    addStep();
    steps.back().moveOutAt(place);
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
    SLL newSll;
    if (steps.size())
        newSll = steps.back().clone();
    else
        newSll = sll.clone();
    steps.push_back(newSll);
    steps.back().finishAnimation();
}

void SLLScene::render() { sll.render(); }

void SLLScene::find(std::string val) {
    addStep();
    SLL &currSll = steps.back();
    Node* curr = currSll.root;
    currSll.deHighlight();
    int nodeIndex = sll.locate(val);
    if (nodeIndex == -1) {
        currSll.highlightTo(sll.nodeCount);
        return;
    }

    for(int i = 0; i < nodeIndex; i++)
        curr = curr->nextNode;

    currSll.highlightTo(nodeIndex); // since node index is actual node - 1;
    curr->borderColor.setBaseColor(BLACK);
    curr->borderColor.setTargetColor(RED);
    curr->borderColor.setFactor(0.f);
}

void SLLScene::mainLoop() {

}