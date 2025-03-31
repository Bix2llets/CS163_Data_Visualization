#include "SLLScene.h"
#include <cstdlib>
float SLLScene::stepDelay = 1.f;
float SLLScene::timeLeft = 0.f;

const Rectangle SLLScene::CANVAS = {100, 100, 1400, 600};
ColorSet const* SLLScene::NODE_PALETTE = &COLOR_SET_1;

float SLLScene::animationRate = 1.0f;
SLL SLLScene::sll(CANVAS, animationRate);
int SLLScene::highlightedRow = -1;

std::deque<SLLScene::SLLStorage> SLLScene::steps;
std::deque<SLLScene::SLLStorage> SLLScene::past;
std::deque<SLLScene::SLLStorage> SLLScene::future;

const Vector2 SLLScene::STARTING_PANE_POSITION = {100, 100};
MenuPane SLLScene::addPane(STARTING_PANE_POSITION, &GBLight::BACKGROUND1,
                           &BUTTON_SET_1, &BUTTON_SET_1);
MenuPane SLLScene::deletePane(STARTING_PANE_POSITION, &GBLight::BACKGROUND1,
                              &BUTTON_SET_1, &BUTTON_SET_1);
MenuPane SLLScene::algoPane(STARTING_PANE_POSITION, &GBLight::BACKGROUND1,
                            &BUTTON_SET_1, &BUTTON_SET_1);
MenuPane SLLScene::miscPane(STARTING_PANE_POSITION, &GBLight::BACKGROUND1,
                            &BUTTON_SET_1, &BUTTON_SET_1);
const std::vector<std::string> SLLScene::PSEUDO_INSERT = {
    "Traverse the linked list", "Create new node", "Update the linked list"};
const std::vector<std::string> SLLScene::PSEUDO_DELETE = {
    "Traverse the linked list", "Delete node", "Update the linked list"};
const std::vector<std::string> SLLScene::PSEUDO_SEARCH = {
    "Traverse the linked list",
    "Return result",
};
void SLLScene::init() {
    steps.push_front({sll, -1});
    addPane.disable();
    algoPane.disable();
    miscPane.disable();
    deletePane.disable();
    addPane.newLine(0, 2, "Add", {"Value", "Location"}, {0, 0}, true);
    addPane.newLine(1, 0, "Random", {}, {}, false);
    deletePane.newLine(0, 1, "Remove", {"Location"}, {0, 0}, true);
    algoPane.newLine(0, 1, "Search", {"Value"}, {0});
    miscPane.newLine(0, 0, "Save", {}, {});
    miscPane.newLine(1, 0, "Load", {}, {});
}
void SLLScene::setDelay(float _stepDelay) { stepDelay = _stepDelay; }
void SLLScene::setPanePosition(Vector2 newPostion) {
    deletePane.setPosition(newPostion);
    addPane.setPosition(newPostion);
    algoPane.setPosition(newPostion);
    miscPane.setPosition(newPostion);
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
    correctAnimation();
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
    correctAnimation();
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
    correctAnimation();
    Color resultColor = GBLight::LIGHT_RED;
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
    curr->borderColor.transitionToward(resultColor);
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
    // ! THIS NEED REVAMP
    // auto location = AppMenu::locationBox.getValue();
    // auto value = AppMenu::valueBox.getValue();
    // auto& buttonPanel = AppMenu::buttonPanel;
    if (addPane.isButtonPressed(1)) {
        addStep(-1, nullptr);
        int length = rand() % 20 + 10;
        SLL &newSll = steps.back().sll;
        while(newSll.nodeCount) 
            newSll.removeEnd();
        for (int i = 0; i < length; i++)
        {

            newSll.addEnd(std::to_string(rand() % 10000));
            newSll.moveAt(newSll.nodeCount - 1);
        }
        newSll.finishAnimation();
        
    }
    if (addPane.isButtonPressed(0)) {
        // * Add at end
        auto value = addPane.getText(0, 0);
        auto location = addPane.getText(0, 1);

        if (isStrNum(value)) {
            if (isStrNum(location)) {
                SLLScene::addAt(value, std::stoi(location));
                AppMenu::loadCode(SLLScene::PSEUDO_INSERT);

            } else if (location.size() == 0) {
                SLLScene::addEnd(value);
                AppMenu::loadCode(SLLScene::PSEUDO_INSERT);
            }

            addPane.getForm(0, 0).clear();
            addPane.getForm(0, 1).clear();
        }
    }

    if (addPane.isRandomPressed(0)) {
        std::string value = std::to_string(rand() % 10000);
        std::string location = std::to_string(rand() % (sll.nodeCount + 1));

        addPane.getForm(0, 0).setText(value);
        addPane.getForm(0, 1).setText(location);
    }
    if (deletePane.isButtonPressed(0)) {
        // * Delete at end and delete at somewhere else
        auto location = deletePane.getText(1, 0);

        if (isStrNum(location)) {
            SLLScene::removeAt(std::stoi(location));
            AppMenu::loadCode(SLLScene::PSEUDO_DELETE);
        } else if (location.size() == 0) {
            SLLScene::removeEnd();
            AppMenu::loadCode(SLLScene::PSEUDO_DELETE);
        }
    }
    if (deletePane.isRandomPressed(0)) {
        std::string location = std::to_string(rand() % (sll.nodeCount + 1));
        deletePane.getForm(0, 0).setText(location);
    }
    if (algoPane.isButtonPressed(0)) {
        auto value = algoPane.getText(2, 0);

        if (isStrNum(value)) {
            SLLScene::find(value);
            AppMenu::loadCode(SLLScene::PSEUDO_SEARCH);
        }
    }
    // if (algoPane.isRandomPressed(0)) {
    //     auto value = rand() % 10000;
    //     algoPane.getForm(0, 0).setText(std::to_string(value));
    // }

    if (miscPane.isButtonPressed(0)) {
        // * Save
        const char* filter[2] = {"*.txt", "*.inp"};
        auto path = tinyfd_saveFileDialog("Save As: ", "output.txt", 2, filter,
                                          "txt or inp file");

        std::cerr << "The path is: " << path << "\n";
        if (path != NULL) {
            SLL& curr = steps.front().sll;
            std::ofstream outputFile(path);
            outputFile << curr.getSaveData();
        }
    }

    if (miscPane.isButtonPressed(1)) {
        const char* filter[2] = {"*.txt", "*.inp"};
        auto path = tinyfd_openFileDialog("Open: ", "", 2, filter,
                                          "txt or inp file", 0);

        if (path != NULL) {
            addStep(-1, nullptr);

            SLL& newSll = steps.back().sll;
            while (newSll.nodeCount) newSll.removeEnd();
            std::ifstream inputFile(path);
            int nodeData;
            while (inputFile >> nodeData) {
                newSll.addEnd(std::to_string(nodeData));
                newSll.moveAt(newSll.nodeCount - 1);
            }
            newSll.finishAnimation();
        }
    }
    if (MenuTable::backwardButton.isPressed()) backward();
    if (MenuTable::forwardButton.isPressed()) forward();
    if (MenuTable::prevButton.isPressed()) prevStep();
    if (MenuTable::nextButton.isPressed()) nextStep();
}

// if (buttonPanel[1][0].isPressed()) {
//     // * Remove at end
//     SLLScene::removeEnd();
//     AppMenu::loadCode(SLLScene::PSEUDO_DELETE);
// }
// if (buttonPanel[0][1].isPressed()) {
//     if (value.first && location.first) {
//         SLLScene::addAt(std::to_string(value.second), location.second);
//         AppMenu::loadCode(SLLScene::PSEUDO_INSERT);
//         AppMenu::locationBox.clear();
//         AppMenu::valueBox.clear();
//     }
// }
// if (buttonPanel[1][1].isPressed()) {
//     if (location.first) {
//         SLLScene::removeAt(location.second);
//         AppMenu::loadCode(SLLScene::PSEUDO_DELETE);
//         AppMenu::locationBox.clear();
//     }
// }
// if (buttonPanel[2][1].isPressed()) {
//     if (value.first) {
//         SLLScene::find(std::to_string(value.second));
//         AppMenu::loadCode(SLLScene::PSEUDO_SEARCH);
//         AppMenu::valueBox.clear();
//     }
// }
// if (AppMenu::undoButton.isPressed()) {
//     prevStep();
//     // Loop::isRunning = false;
// }
// if (AppMenu::redoButton.isPressed()) {
//     nextStep();
//     // Loop::isRunning = true;
// }
// if (AppMenu::backwardButton.isPressed()) {
//     backward();
//     // Loop::isRunning = false;
// }
// if (AppMenu::forwardButton.isPressed()) {
//     forward();
//     // Loop::isRunning = true;
// }

void SLLScene::nextStep() {
    if (steps.size() > 1) {
        past.push_back(steps.front());
        steps.pop_front();

        sll = steps.front().sll.clone();
        highlightedRow = steps.front().highlightIndex;
        if (steps.front().highlightRef)
            AppMenu::loadCode(*steps.front().highlightRef);
    } else {
        if (future.size() == 0) return;
        steps.push_back(future.front());
        future.pop_front();
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

void SLLScene::correctAnimation() {
    if (future.size() == 0) return;
    while (steps.front().highlightIndex != -1) nextStep();
}

void SLLScene::backward() {
    while (past.size()) {
        prevStep();
        if (steps.front().highlightIndex == -1) break;
    }
    sll = steps.front().sll;
    sll.finishAnimation();
    highlightedRow = steps.front().highlightIndex;
    if (steps.front().highlightRef)
        AppMenu::loadCode(*steps.front().highlightRef);
}

void SLLScene::forward() {
    if (steps.size() > 1 || future.size()) {
        auto& temp = steps.front();
        while (steps.size() > 1 || future.size()) {
            nextStep();
            if (&temp != &steps.front() && steps.front().highlightIndex == -1)
                break;
        }
    }
    sll.finishAnimation();
}
