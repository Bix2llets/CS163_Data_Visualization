#include "SLLScene.h"

float SLLScene::stepDelay = 1.f;
float SLLScene::timeLeft = 0.f;

const Rectangle SLLScene::CANVAS = {50, 50, 1500, 550};
float SLLScene::animationRate = 1.0f;
SLL SLLScene::sll(CANVAS, animationRate);
int SLLScene::highlightedRow = 0;

std::deque<SLLScene::SLLStorage> SLLScene::steps;
std::deque<SLLScene::SLLStorage> SLLScene::past;

const std::vector<std::string> SLLScene::PSEUDO_DELETE_K = {
    "Node* prev = nullptr;",
    "while(curr && curr->pNext) prev = curr, curr = curr->pNext;",
    "if (curr == nullptr) delete curr and update the tree",

};
const std::vector<std::string> SLLScene::PSEUDO_INSERT_K = {
    "while (k && curr) k--, curr = curr->pNext;",
    "if (curr == nullptr) create new node and update the linked list",
};
const std::vector<std::string> SLLScene::PSEUDO_DELETE_END = {
    "Node* prev = nullptr",
    "while(curr && curr->pNext) prev = curr, curr = curr->pNext;",
    "if (curr == nullptr) delete curr and update the linked list",
};
const std::vector<std::string> SLLScene::PSEUDO_INSERT_END = {
    "while(curr && curr->pNext) curr = curr->pNext;",
    "create new node and update the linked list"};
const std::vector<std::string> SLLScene::PSEUDO_SEARCH = {
    "while(curr && curr->value != k) curr = curr->pNext;",
    "return curr;",
};
void SLLScene::setSpecs(float _stepDelay, float _animationRate) {
    stepDelay = _stepDelay;
    animationRate = _animationRate;
    sll.setAnimationRate(animationRate);
}
void SLLScene::addEnd(std::string data) {
    addStep(0);
    steps.back().sll.highlightTo(steps.back().sll.nodeCount - 1);
    addStep(1);
    steps.back().sll.addEnd(data);
};
void SLLScene::addAt(std::string data, int place) {
    if (steps.size()) {
        if (place > steps.back().sll.nodeCount + 1) return;
    } else {
        if (place > sll.nodeCount + 1) return;
    }
    place--;
    addStep(0);
    steps.back().sll.deHighlight();
    steps.back().sll.highlightTo(place - 1);
    addStep(1);
    steps.back().sll.shiftForward(place);
    addStep(1);
    steps.back().sll.addAt(data, place);
    std::cerr << steps.back().sll.nodeCount << "\n";
};
void SLLScene::removeEnd() {
    addStep(1);
    steps.back().sll.deHighlight();
    steps.back().sll.highlightTo(steps.back().sll.nodeCount - 1);
    addStep(2);
    steps.back().sll.moveOutEnd();
    addStep(2);
    steps.back().sll.removeEnd();
};
void SLLScene::removeAt(int place) {
    std::cerr << "Begin remove at\n";
    place--;
    if (steps.size()) {
        std::cerr << "Checking: " << place << steps.back().sll.nodeCount << "\n";
        if (place >= steps.back().sll.nodeCount) {
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
    addStep(1);
    steps.back().sll.deHighlight();
    steps.back().sll.highlightTo(place);
    addStep(2);
    steps.back().sll.moveOutAt(place);
    addStep(2);
    steps.back().sll.removeAt(place);
    addStep(2);
    steps.back().sll.shiftBackward(place);
};
void SLLScene::update() {
    sll.update();
    if (!sll.isFinished()) return;

    timeLeft -= GetFrameTime();
    if (abs(timeLeft) < 1e-6) timeLeft = 0;
    if (timeLeft <= 0) timeLeft = 0;

    if (timeLeft == 0 && steps.size()) {
        past.push_back({sll, highlightedRow});
        
        sll = steps.front().sll;
        highlightedRow = steps.front().highlightIndex;

        steps.pop_front();
        timeLeft = steps.size() ? stepDelay : 0;
    }
};
void SLLScene::addStep(int highlightIndex) {
    SLL newSll;
    if (steps.size())
        newSll = steps.back().sll.clone();
    else
        newSll = sll.clone();
    newSll.finishAnimation();
    steps.push_back({newSll, highlightIndex});
}

void SLLScene::render() { sll.render(); }

void SLLScene::find(std::string val) {
    addStep(0);
    SLL& currSll = steps.back().sll;
    Node* curr = currSll.root;
    currSll.deHighlight();
    int nodeIndex = sll.locate(val);
    if (nodeIndex == -1) {
        currSll.highlightTo(sll.nodeCount);
        return;
    }

    for (int i = 0; i < nodeIndex; i++) curr = curr->nextNode;

    currSll.highlightTo(nodeIndex);  // since node index is actual node - 1;
    curr->borderColor.setBaseColor(BLACK);
    curr->borderColor.setTargetColor(RED);
    curr->borderColor.setFactor(0.f);
    addStep(1);
}

void SLLScene::clearScene() {
    sll = SLL(CANVAS, animationRate);
    highlightedRow = 0;
    setSpecs(1.f, 1.f);
    timeLeft = 0;

}