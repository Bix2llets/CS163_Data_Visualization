#include "menu.h"

#include "menuPane.h"
#include "raygui.h"
namespace MenuTable {
Vector2 optionPosition = {10, 660};
Vector2 optionDimension = {200, 50};

Vector2 sliderBarPos = {400, 400};
Vector2 sliderBarDimension = {50, 50};

Vector2 buttonPos = {600, 750};
Vector2 buttonDimension = {50, 50};
Vector2 buttonDistance = {10, 0};

float minValue = 0.01f, maxValue = 5.f, sliderValue = 1.f;

TextureBox backwardButton =
    TextureBox(buttonPos, sliderBarDimension, (Rectangle){0, 0, 100, 100},
               &Utility::backward, &buttonColorSet);
TextureBox forwardButton = TextureBox(
    (Vector2){buttonPos.x + (buttonDimension.x + buttonDistance.x) * 4,
              buttonPos.y},
    buttonDimension, (Rectangle){0, 0, 100, 100}, &Utility::forward,
    &buttonColorSet);
TextureBox playButton = TextureBox(
    (Vector2){buttonPos.x + (buttonDimension.x + buttonDistance.x) * 2,
              buttonPos.y},
    buttonDimension, (Rectangle){0, 0, 100, 100}, &Utility::pause,
    &buttonColorSet);
TextureBox pauseButton = TextureBox(
    (Vector2){buttonPos.x + (buttonDimension.x + buttonDistance.x) * 2,
              buttonPos.y},
    buttonDimension, (Rectangle){0, 0, 100, 100}, &Utility::expand,
    &buttonColorSet);
TextureBox prevButton =
    TextureBox((Vector2){buttonPos.x + (buttonDimension.x + buttonDistance.x),
                         buttonPos.y},
               buttonDimension, (Rectangle){0, 0, 100, 100}, &Utility::prev,
               &buttonColorSet);
TextureBox nextButton = TextureBox(
    (Vector2){buttonPos.x + (buttonDimension.x + buttonDistance.x) * 3,
              buttonPos.y},
    buttonDimension, (Rectangle){0, 0, 100, 100}, &Utility::next,
    &buttonColorSet);
Button showMenu = Button(optionPosition,
                         (Vector2){sliderBarDimension.y, sliderBarDimension.x},
                         ">", 20, &buttonColorSet);
bool showMenuFlag = false, *isPlaying = &Loop::isRunning;
// * For menu panes
MenuPane basePane({optionPosition.x + 10 + showMenu.getDimension().x,
                   optionPosition.y},
                  &paneBackground, &buttonColorSet, &buttonColorSet);
MenuPane* addPane;
MenuPane* deletePane;
MenuPane* algoPane;
MenuPane* storagePane;
void Constructor(Vector2 _optionPosition = {10, 600},
                 Vector2 _optionDimension = {200, 50},
                 Vector2 _sliderBarPos = {500, 400},
                 Vector2 _sliderBarDimension = {50, 50}) {
    optionPosition = _optionPosition;
    optionDimension = _optionDimension;
    sliderBarPos = _sliderBarPos;
    sliderBarDimension = _sliderBarDimension;

    basePane.newLine(0, 0, "Add", {}, {}, false);
    basePane.newLine(1, 0, "Remove", {}, {}, false);
    basePane.newLine(2, 0, "Algorithm", {}, {}, false);
    basePane.newLine(3, 0, "Storage", {}, {}, false);

    addPane = nullptr;
    deletePane = nullptr;
    algoPane = nullptr;
    storagePane = nullptr;
    showMenu.setDimension(
        {showMenu.getDimension().x, basePane.getDimension().y});
    showMenuFlag = false;
    isPlaying = &Loop::isRunning;
    continueAnimation();
}

void init() {
    pauseButton.disable();
    playButton.enable();
}

void render() {
    handleInput();
    showMenu.render();
    if (showMenuFlag) {
        basePane.render();
        if (addPane) addPane->render();
        if (deletePane) deletePane->render();
        if (algoPane) algoPane->render();
        if (storagePane) storagePane->render();
    }
    backwardButton.render();
    forwardButton.render();

    pauseButton.render();
    playButton.render();
    prevButton.render();
    nextButton.render();
    ///* Slider bar **/
    Vector2 centerPauseButton =
        Vector2Add(pauseButton.getPosition(),
                   Vector2Scale(pauseButton.getDimension(), 0.5f));
    Vector2 sliderPosition = Vector2Add(
        centerPauseButton, Vector2{-sliderBarDimension.x * 3 / 2, 50});
    GuiSliderBar(
        (Rectangle){sliderPosition.x, sliderPosition.y,
                    sliderBarDimension.x * 3, sliderBarDimension.y / 2},
        "Speed", TextFormat("%.2fx", sliderValue), &sliderValue, minValue,
        maxValue);

    // Update animation speed based on slider value
    Animation::setUpdateRate(sliderValue);
    AnimationColor::setUpdateRate(sliderValue);
    AVLState::setAnimationSpeed(sliderValue);
    TrieState::setAnimationSpeed(sliderValue);
    HashState::setAnimationSpeed(sliderValue);
}

void handleInput() {
    if (showMenu.isPressed()) {
        showMenuFlag = !showMenuFlag;
    }
    if (showMenuFlag)
        showMenu.setText("<");
    else {
        showMenu.setText(">");
        if (addPane) addPane->disable();
        if (deletePane) deletePane->disable();
        if (algoPane) algoPane->disable();
        if (storagePane) storagePane->disable();
    }
    if (showMenuFlag) {
        if (basePane.isButtonPressed(0) == true) {
            if (addPane) addPane->toggle();
            if (deletePane) deletePane->disable();
            if (algoPane) algoPane->disable();
            if (storagePane) storagePane->disable();
        }
        if (basePane.isButtonPressed(1) == true) {
            if (addPane) addPane->disable();
            if (deletePane) deletePane->toggle();
            if (algoPane) algoPane->disable();
            if (storagePane) storagePane->disable();
        }
        if (basePane.isButtonPressed(2) == true) {
            if (addPane) addPane->disable();
            if (deletePane) deletePane->disable();
            if (algoPane) algoPane->toggle();
            if (storagePane) storagePane->disable();
        }
        if (basePane.isButtonPressed(3) == true) {
            if (addPane) addPane->disable();
            if (deletePane) deletePane->disable();
            if (algoPane) algoPane->disable();
            if (storagePane) storagePane->toggle();
        }
    }
    if (playButton.isPressed()) {
        pauseAnimation();
    } else if (pauseButton.isPressed()) {
        continueAnimation();
    }

    if (prevButton.isPressed()) {
        pauseAnimation();
    }

    if (backwardButton.isPressed()) {
        // pauseAnimation();
    }
}

void pauseAnimation() {
    Loop::isRunning = false;
    playButton.disable();
    pauseButton.enable();
}

void continueAnimation() {
    Loop::isRunning = true;
    pauseButton.disable();
    playButton.enable();
}
};  // namespace MenuTable
