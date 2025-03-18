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
void SLLScene::init() { steps.push_front({sll, -1});}
void SLLScene::setSpecs(float _stepDelay) {
    stepDelay = _stepDelay;
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
    if (steps.size() > 1) return;
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

    if (timeLeft == 0 && steps.size() > 1) {
        past.push_back(steps.front());
        steps.pop_front();

        sll = steps.front().sll.clone();
        highlightedRow = steps.front().highlightIndex;

        timeLeft = steps.size() ? stepDelay : 0;
    }
};
void SLLScene::addStep(int highlightIndex) {
    while (future.size()) {
        future.pop_back();
    }
    SLL newSll;
    if (steps.size())
        newSll = steps.back().sll.clone();
    else
        newSll = sll.clone();
    newSll.finishAnimation();
    steps.push_back({newSll, highlightIndex});
    if (highlightIndex == -1) future.push_front({newSll, highlightIndex});
}

void SLLScene::render() { sll.render(); }

void SLLScene::find(std::string val) {
    if (steps.size() > 1) return;
    addStep(0);
    SLL& currSll = steps.back().sll;
    Node* curr = currSll.root;
    currSll.deHighlight();
    int nodeIndex = sll.locate(val);
    if (nodeIndex == -1) {
        currSll.highlightTo(sll.nodeCount);
        addStep(-1);
        return;
    }

    for (int i = 0; i < nodeIndex; i++) curr = curr->nextNode;
    
    currSll.highlightTo(nodeIndex);  // since node index is actual node - 1;
    curr->borderColor.setBaseColor(SLLScene::NODE_PALETTE.borderNormal);
    curr->borderColor.setTargetColor(resultColor);
    curr->borderColor.setFactor(0.f);
    addStep(1);
    addStep(-1);
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
    if (AppMenu::undoButton.isPressed()) {
        prevStep();
    }
    if (AppMenu::redoButton.isPressed()) {
        nextStep();
    }
}

void SLLScene::prevStep() {
    if (past.size() == 0) return;
    if (future.size() == 0) {
        for (auto &element: steps) future.push_back(element);
    }
    while (steps.size()) {
        steps.pop_back();
    };
    std::cerr << "Before: \n";
    for (auto x: past) std::cerr << x.highlightIndex << " ";
    std::cerr << "\n";
    for (auto x: future) std::cerr << x.highlightIndex << " ";
    std::cerr << "\n";
    
    while (true) {
        future.push_front(past.back());
        past.pop_back();
        if (future.front().highlightIndex == -1) {
            steps.push_front(future.front());
            sll = steps.front().sll.clone();
            highlightedRow = steps.front().highlightIndex;
            break;
        }
    }
    std::cerr << "After: \n";
    for (auto x: past) std::cerr << x.highlightIndex << " ";
    std::cerr << "\n";
    for (auto x: future) std::cerr << x.highlightIndex << " ";
    std::cerr << "\n";
    std::cerr << "--------------------------\n\n";

    // ! BUG IN PREV STEP, NEXT STEP AND ADD STEP 
    // ! URGENT FIX
}

void SLLScene::nextStep() {
    if (future.size() <= 1) return;
    while (steps.size()) {
        steps.pop_back();
    }
    std::cerr << "Before: \n";
    for (auto x: past) std::cerr << x.highlightIndex << " ";
    std::cerr << "\n";
    for (auto x: future) std::cerr << x.highlightIndex << " ";
    std::cerr << "\n";
    while (true) {
        past.push_back(future.front());
        future.pop_front();
        if (future.front().highlightIndex == -1) {
            steps.push_front(future.front());
            sll = steps.front().sll.clone();
            highlightedRow = steps.front().highlightIndex;
            break;
        }
    }
    std::cerr << "After: \n";
    for (auto x: past) std::cerr << x.highlightIndex << " ";
    std::cerr << "\n";
    for (auto x: future) std::cerr << x.highlightIndex << " ";
    std::cerr << "\n";
    std::cerr << "--------------------------\n\n";
}
