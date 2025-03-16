#include "SLLScene.h"

float SLLScene::stepDelay = 1.f;
float SLLScene::timeLeft = 0.f;

const Rectangle SLLScene::CANVAS = {50, 50, 1500, 550};
const ColorSet SLLScene::NODE_PALETTE = {
    Color{186, 180, 163, 255}, Color{186, 180, 163, 255},
    Color{51, 49, 45, 255},    Color{42, 114, 47, 255},
    Color{186, 180, 163, 255}, Color{229, 189, 80, 255},
};

const Color resultColor = {191, 97, 106, 255};
float SLLScene::animationRate = 1.0f;
SLL SLLScene::sll(CANVAS, animationRate);
int SLLScene::highlightedRow = -1;

std::deque<SLLScene::SLLStorage> SLLScene::steps;
std::deque<SLLScene::SLLStorage> SLLScene::past;

const std::vector<std::string> SLLScene::PSEUDO_INSERT = {
    "Traverse the linked list", "Create new node", "Update the linked list"};
const std::vector<std::string> SLLScene::PSEUDO_DELETE = {
    "Traverse the linked list", "Delete node", "Update the linked list"};
const std::vector<std::string> SLLScene::PSEUDO_SEARCH = {
    "Traverse the linked list",
    "Return result",
};
void SLLScene::setSpecs(float _stepDelay, float _animationRate) {
    stepDelay = _stepDelay;
    animationRate = _animationRate;
    sll.setAnimationRate(animationRate);
}
void SLLScene::addEnd(std::string data) {
    int place = 0;
    if (steps.size())
        place = steps.back().sll.nodeCount;
    else
        place = sll.nodeCount;

    addAt(data, place);
};
void SLLScene::addAt(std::string data, int place) {
    int size = 0;
    if (steps.size())
        size = steps.back().sll.nodeCount;
    else
        size = sll.nodeCount;
    if (place > size) {
        addStep(0);
        steps.back().sll.deHighlight();
        steps.back().sll.highlightTo(size);
        addStep(-1);
        steps.back().sll.deHighlight();
        return;
    }
    addStep(0);
    steps.back().sll.deHighlight();
    steps.back().sll.highlightTo(place - 1);
    addStep(1);
    steps.back().sll.addAt(data, place);
    addStep(2);
    steps.back().sll.shiftForward(place + 1);
    addStep(2);
    steps.back().sll.moveAt(place);
    addStep(-1);
    steps.back().sll.deHighlight();
};
void SLLScene::removeEnd() {
    int place = 0;
    if (steps.size())
        place = steps.back().sll.nodeCount;
    else
        place = sll.nodeCount;

    removeAt(place);
};
void SLLScene::removeAt(int place) {
    int size = 0;
    if (steps.size())
        size = steps.back().sll.nodeCount;
    else
        size = sll.nodeCount;
    if (place > size || size == 0) {
        addStep(0);
        steps.back().sll.deHighlight();
        steps.back().sll.highlightTo(size);
        addStep(-1);
        steps.back().sll.deHighlight();
        return;
    }
    addStep(0);
    steps.back().sll.deHighlight();
    steps.back().sll.highlightTo(place);
    addStep(1);
    steps.back().sll.moveAt(place);
    addStep(1);
    steps.back().sll.removeAt(place);
    addStep(2);
    steps.back().sll.shiftBackward(place);
    addStep(-1);
    steps.back().sll.deHighlight();
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
    curr->borderColor.setBaseColor(SLLScene::NODE_PALETTE.borderNormal);
    curr->borderColor.setTargetColor(resultColor);
    curr->borderColor.setFactor(0.f);
    addStep(1);
}

void SLLScene::clearScene() {
    sll = SLL(CANVAS, animationRate);
    highlightedRow = 0;
    setSpecs(1.f, 1.f);
    timeLeft = 0;
}

void SLLScene::recordInput() {
    auto location = AppMenu::locationBox.getValue();
    auto value = AppMenu::valueBox.getValue();
    auto& buttonPanel = AppMenu::buttonPanel;
    if (buttonPanel[0][0].isPressed()) {
        // * Add at end
        if (value.first) {
            SLLScene::addEnd(std::to_string(value.second));
            AppMenu::loadCode(SLLScene::PSEUDO_INSERT);
        }
    }
    if (buttonPanel[1][0].isPressed()) {
        // * Remove at end
        SLLScene::removeEnd();
        AppMenu::loadCode(SLLScene::PSEUDO_DELETE);
    }
    if (buttonPanel[0][1].isPressed()) {
        if (value.first && location.first) {
            SLLScene::addAt(std::to_string(value.second), location.second);
            AppMenu::loadCode(SLLScene::PSEUDO_INSERT);
        }
    }
    if (buttonPanel[1][1].isPressed()) {
        if (location.first) {
            SLLScene::removeAt(location.second);
            AppMenu::loadCode(SLLScene::PSEUDO_DELETE);
        }
    }
    if (buttonPanel[2][1].isPressed()) {
        if (value.first) {
            SLLScene::find(std::to_string(value.second));
            AppMenu::loadCode(SLLScene::PSEUDO_SEARCH);
        }
    }
}
