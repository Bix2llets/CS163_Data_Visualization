#include "SLLScene.h"

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

void SLLScene::render() {
    sll.render();
    AddMenu::render();
    DeleteMenu::render();
    AlgorithmMenu::render();
}

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
    if (AppMenu::backwardButton.isPressed()) {
        backward();
        // Loop::isRunning = false;
    }
    if (AppMenu::forwardButton.isPressed()) {
        forward();
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
}

namespace SLLScene {

const Vector2 BUTTON_DIMENSION = {160, 20};
const Vector2 BUTTON_DISTANCE = {30, 30};
const Vector2 FORM_DIMENSION = {160, 25};
const Vector2 STARTING_POSITION = {120, 500};
}  // namespace SLLScene
namespace SLLScene::AddMenu {
Button addEndButton(STARTING_POSITION, BUTTON_DIMENSION, "Add at End", 12,
                    &BUTTON_SET_1, &DrawUtility::inter12);

Button addAtButton({STARTING_POSITION.x + BUTTON_DIMENSION.x +
                        BUTTON_DISTANCE.x,
                    STARTING_POSITION.y},
                   BUTTON_DIMENSION, "Add at Location", 12, &BUTTON_SET_1,
                   &DrawUtility::inter12);

Form locationForm({STARTING_POSITION.x,
                   STARTING_POSITION.y + BUTTON_DIMENSION.y + BUTTON_DISTANCE.y,
                   FORM_DIMENSION.x, FORM_DIMENSION.y},
                  &BUTTON_SET_1);
Form valueForm({STARTING_POSITION.x + BUTTON_DIMENSION.x + BUTTON_DISTANCE.x,
                STARTING_POSITION.y + BUTTON_DIMENSION.y + BUTTON_DISTANCE.y,
                FORM_DIMENSION.x, FORM_DIMENSION.y},
               &BUTTON_SET_1);

bool enabled = false;
void render() {
    setToggle(enabled);
    if (!enabled) return;
    
    DrawRectangle(STARTING_POSITION.x - 10, STARTING_POSITION.y - 10,
                  BUTTON_DIMENSION.x * 2 + 20 + BUTTON_DISTANCE.x,
                  FORM_DIMENSION.y * 2 + 20 + BUTTON_DISTANCE.y,
                  GBLight::BACKGROUND3);

    addEndButton.render();
    addAtButton.render();
    locationForm.render();
    valueForm.render();
    // * Render necessary text

    Vector2 textLocationPos = locationForm.getPosition();
    textLocationPos.x += FORM_DIMENSION.x / 2;
    textLocationPos.y -= 10;

    Vector2 textValuePos = valueForm.getPosition();
    textValuePos.x += FORM_DIMENSION.x / 2;
    textValuePos.y -= 10;

    DrawUtility::drawText("Location", textLocationPos, DrawUtility::inter16,
                          BUTTON_SET_1.textNormal, 16, DrawUtility::SPACING,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
    DrawUtility::drawText("Value", textValuePos, DrawUtility::inter16,
                          BUTTON_SET_1.textNormal, 16, DrawUtility::SPACING,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
}

void toggle() { setToggle(!enabled); }

void setToggle(bool state) {
    enabled = state;
    addEndButton.set(state);
    addAtButton.set(state);
    locationForm.set(state);
    valueForm.set(state);
}
}  // namespace SLLScene::AddMenu
namespace SLLScene::DeleteMenu {
Button deleteEndButton(STARTING_POSITION, BUTTON_DIMENSION, "Delete at End", 12,
                       &BUTTON_SET_1, &DrawUtility::inter12);

Button deleteAtButton({STARTING_POSITION.x + BUTTON_DIMENSION.x +
                           BUTTON_DISTANCE.x,
                       STARTING_POSITION.y},
                      BUTTON_DIMENSION, "Delete at Location", 12, &BUTTON_SET_1,
                      &DrawUtility::inter12);

Form locationForm({STARTING_POSITION.x,
                   STARTING_POSITION.y + BUTTON_DIMENSION.y + BUTTON_DISTANCE.y,
                   FORM_DIMENSION.x, FORM_DIMENSION.y},
                  &BUTTON_SET_1);
Form valueForm({STARTING_POSITION.x + BUTTON_DIMENSION.x + BUTTON_DISTANCE.x,
                STARTING_POSITION.y + BUTTON_DIMENSION.y + BUTTON_DISTANCE.y,
                FORM_DIMENSION.x, FORM_DIMENSION.y},
               &BUTTON_SET_1);

bool enabled = false;
void render() {
    setToggle(enabled);
    if (!enabled) return;
    DrawRectangle(STARTING_POSITION.x - 10, STARTING_POSITION.y - 10,
                  BUTTON_DIMENSION.x * 2 + 20 + BUTTON_DISTANCE.x,
                  FORM_DIMENSION.y * 2 + 20 + BUTTON_DISTANCE.y,
                  GBLight::BACKGROUND3);

    deleteEndButton.render();
    deleteAtButton.render();
    locationForm.render();
    valueForm.render();
    // * Render necessary text

    Vector2 textLocationPos = locationForm.getPosition();
    textLocationPos.x += FORM_DIMENSION.x / 2;
    textLocationPos.y -= 10;

    Vector2 textValuePos = valueForm.getPosition();
    textValuePos.x += FORM_DIMENSION.x / 2;
    textValuePos.y -= 10;

    DrawUtility::drawText("Location", textLocationPos, DrawUtility::inter16,
                          BUTTON_SET_1.textNormal, 16, DrawUtility::SPACING,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
    DrawUtility::drawText("Value", textValuePos, DrawUtility::inter16,
                          BUTTON_SET_1.textNormal, 16, DrawUtility::SPACING,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
}

void toggle() { setToggle(!enabled); }

void setToggle(bool state) {
    enabled = state;
    valueForm.set(state);
    locationForm.set(state);
    deleteAtButton.set(state);
    deleteEndButton.set(state);
}
}  // namespace SLLScene::DeleteMenu

namespace SLLScene::AlgorithmMenu {
Button searchButton{STARTING_POSITION, BUTTON_DIMENSION,     "Search", 16,
                    &BUTTON_SET_1,     &DrawUtility::inter16};

Form valueForm{{STARTING_POSITION.x,
                STARTING_POSITION.y + BUTTON_DIMENSION.y + BUTTON_DISTANCE.y,
                FORM_DIMENSION.x, FORM_DIMENSION.y},
               &BUTTON_SET_1};

bool enabled = false;
void recordInput() { valueForm.update(); }
void render() {
    setToggle(enabled);
    if (!enabled) return;
    DrawRectangle(
        STARTING_POSITION.x - 10, STARTING_POSITION.y - 10,
        20 + BUTTON_DIMENSION.x,
        20 + BUTTON_DIMENSION.y + BUTTON_DISTANCE.y + FORM_DIMENSION.y,
        GBLight::BACKGROUND1);
    searchButton.render();
    valueForm.render();
    Vector2 textPosition = valueForm.getPosition();
    textPosition.x += FORM_DIMENSION.x / 2;
    textPosition.y -= 10;
    DrawUtility::drawText("Value", textPosition, DrawUtility::inter16,
                          COLOR_SET_1.textNormal, 16, DrawUtility::SPACING,
                          VerticalAlignment::CENTERED,
                          HorizontalAlignment::CENTERED);
}

void toggle() { setToggle(!enabled); }

void setToggle(bool state) {
    enabled = state;
    searchButton.set(state);
    valueForm.set(state);
}  // namespace SLLScene::AlgorithmMenu
}