#include "SLLScene.h"

float SLLScene::stepDelay = 1.f;
float SLLScene::timeLeft = 0.f;

const Rectangle SLLScene::CANVAS = {100, 100, 1400, 600};
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
std::deque<SLLScene::SLLStorage> SLLScene::future;

const std::vector<std::string> SLLScene::PSEUDO_INSERT = {
    "Traverse the linked list", "Create new node", "Update the linked list"};
const std::vector<std::string> SLLScene::PSEUDO_DELETE = {
    "Traverse the linked list", "Delete node", "Update the linked list"};
const std::vector<std::string> SLLScene::PSEUDO_SEARCH = {
    "Traverse the linked list",
    "Return result",
};
void SLLScene::init() { steps.push_front({sll, -1}); }
void SLLScene::setSpecs(float _stepDelay) { stepDelay = _stepDelay; }
void SLLScene::addEnd(std::string data) {
    int place = 0;
    if (steps.size())
        place = steps.back().sll.nodeCount;
    else
        place = sll.nodeCount;

    addAt(data, place);
};
void SLLScene::addAt(std::string data, int place) {
    if (steps.size() > 1) return;
    int size = 0;
    if (steps.size())
        size = steps.back().sll.nodeCount;
    else
        size = sll.nodeCount;
    if (place > size) {
        addStep(0, &PSEUDO_INSERT);
        steps.back().sll.deHighlight();
        steps.back().sll.highlightTo(size);
        addStep(-1, &PSEUDO_INSERT);
        steps.back().sll.deHighlight();
        return;
    }
    addStep(0, &PSEUDO_INSERT);
    steps.back().sll.deHighlight();
    steps.back().sll.highlightTo(place - 1);
    addStep(1, &PSEUDO_INSERT);
    steps.back().sll.addAt(data, place);
    if (place + 1 <= steps.back().sll.nodeCount) {
        addStep(2, &PSEUDO_INSERT);
        steps.back().sll.shiftForward(place + 1);
    }
    addStep(2, &PSEUDO_INSERT);
    steps.back().sll.moveAt(place);
    addStep(-1, &PSEUDO_INSERT);
    steps.back().sll.deHighlight();
};
void SLLScene::removeEnd() {
    int place = 0;
    if (steps.size())
        place = steps.back().sll.nodeCount - 1;
    else
        place = sll.nodeCount - 1;

    removeAt(place);
};
void SLLScene::removeAt(int place) {
    if (steps.size() > 1) return;
    int size = 0;
    if (steps.size())
        size = steps.back().sll.nodeCount;
    else
        size = sll.nodeCount;
    if (place > size || size == 0) {
        addStep(0, &PSEUDO_DELETE);
        steps.back().sll.deHighlight();
        steps.back().sll.highlightTo(size);
        addStep(-1, &PSEUDO_DELETE);
        steps.back().sll.deHighlight();
        return;
    }
    addStep(0, &PSEUDO_DELETE);
    steps.back().sll.deHighlight();
    steps.back().sll.highlightTo(place);
    addStep(1, &PSEUDO_DELETE);
    steps.back().sll.moveAt(place);
    addStep(1, &PSEUDO_DELETE);
    steps.back().sll.removeAt(place);
    addStep(2, &PSEUDO_DELETE);
    steps.back().sll.shiftBackward(place);
    addStep(-1, &PSEUDO_DELETE);
    steps.back().sll.deHighlight();
};
void SLLScene::update() {
    sll.update();
    if (!sll.isFinished()) return;

    timeLeft -= GetFrameTime();
    if (abs(timeLeft) < 1e-6) timeLeft = 0;
    if (timeLeft <= 0) timeLeft = 0;

    if (timeLeft == 0 && steps.size() > 1) {
        past.push_back(steps.front());
        steps.pop_front();

        sll = steps.front().sll.clone();
        highlightedRow = steps.front().highlightIndex;
        if (steps.front().highlightRef != nullptr)
            AppMenu::loadCode(*steps.front().highlightRef);
        timeLeft = steps.size() ? stepDelay : 0;
    }
};
void SLLScene::addStep(int highlightIndex,
                       std::vector<std::string> const* ref) {
    while (future.size()) {
        future.pop_back();
    }
    SLL newSll;
    if (steps.size())
        newSll = steps.back().sll.clone();
    else
        newSll = sll.clone();
    newSll.finishAnimation();
    SLLStorage newStorage;
    newStorage.sll = newSll;
    newStorage.highlightIndex = highlightIndex;
    newStorage.highlightRef = ref;
    steps.push_back(newStorage);
    // if (highlightIndex == -1) future.push_front(newStorage);
}

void SLLScene::render() { sll.render(); }

void SLLScene::find(std::string val) {
    if (steps.size() > 1) return;
    addStep(0, &PSEUDO_SEARCH);
    SLL& currSll = steps.back().sll;
    Node* curr = currSll.root;
    currSll.deHighlight();
    int nodeIndex = sll.locate(val);
    if (nodeIndex == -1) {
        currSll.highlightTo(sll.nodeCount);
        addStep(-1, &PSEUDO_SEARCH);
        return;
    }

    for (int i = 0; i < nodeIndex; i++) curr = curr->nextNode;

    currSll.highlightTo(nodeIndex);  // since node index is actual node - 1;
    curr->borderColor.setBaseColor(SLLScene::NODE_PALETTE.borderNormal);
    curr->borderColor.setTargetColor(resultColor);
    curr->borderColor.setFactor(0.f);
    addStep(1, &PSEUDO_SEARCH);
    addStep(-1, &PSEUDO_SEARCH);
}

void SLLScene::clearScene() {
    sll = SLL(CANVAS, animationRate);
    while (steps.size()) {
        steps.front().sll.freeMemory();
        steps.pop_front();
    }
    while (past.size()) {
        past.back().sll.freeMemory();
        past.pop_back();
    }
    highlightedRow = 0;
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
            AppMenu::valueBox.clear();
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
            AppMenu::locationBox.clear();
            AppMenu::valueBox.clear();
        }
    }
    if (buttonPanel[1][1].isPressed()) {
        if (location.first) {
            SLLScene::removeAt(location.second);
            AppMenu::loadCode(SLLScene::PSEUDO_DELETE);
            AppMenu::locationBox.clear();
        }
    }
    if (buttonPanel[2][1].isPressed()) {
        if (value.first) {
            SLLScene::find(std::to_string(value.second));
            AppMenu::loadCode(SLLScene::PSEUDO_SEARCH);
            AppMenu::valueBox.clear();
        }
    }
    if (AppMenu::undoButton.isPressed()) {
        prevStep();
        // Loop::isRunning = false;
    }
    if (AppMenu::redoButton.isPressed()) {
        nextStep();
        // Loop::isRunning = true;
    }
}

void SLLScene::nextStep() {
    if (future.size()) {
        // * Result from previous undo
        steps.push_back(future.front());
        future.pop_front();
        // sll = steps.front().sll.clone();
        // highlightedRow = steps.front().highlightIndex;
        return;
    } else {
        if (steps.size() == 1) return;
        // * There are more in steps
        past.push_back(steps.front());
        steps.pop_front();

        sll = steps.front().sll.clone();
        highlightedRow = steps.front().highlightIndex;
        if (steps.front().highlightRef)
        AppMenu::loadCode(*steps.front().highlightRef);
    }
}

void SLLScene::prevStep() {
    if (past.size() == 0) return;
    // * There is animation in queue, future has none
    // * Transfer the rest into future
    while (steps.size() > 1) {
        future.push_front(steps.back());
        steps.pop_back();
    }
    // * NO animation queuing
    future.push_front(steps.front());
    steps.pop_front();
    steps.push_front(past.back());
    past.pop_back();

    sll = steps.front().sll.clone();
    highlightedRow = steps.front().highlightIndex;
    if (steps.front().highlightRef)
        AppMenu::loadCode(*steps.front().highlightRef);
    sll.finishAnimation();
}
