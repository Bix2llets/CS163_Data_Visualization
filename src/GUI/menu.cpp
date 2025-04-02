#include "menu.hpp"

#include "menuPane.h"
#include "raygui.h"
namespace MenuTable {
Vector2 optionPosition = {10, 650};
Vector2 optionDimension = {200, 50};

Vector2 sliderBarPos = {400, 400};
Vector2 sliderBarDimension = {50, 50};

Vector2 buttonPos = {600, 750};
Vector2 buttonDimension = {50, 50};
Vector2 buttonDistance = {10, 0};

float minValue = 0.5f, maxValue = 5.f, sliderValue = 1.f;

int MaxSizeNum = 3, MaxSizeText = 5, MaxSizeWeight = 5;
TextureBox backwardButton =
    TextureBox(buttonPos, sliderBarDimension, (Rectangle){0, 0, 100, 100},
               &mLib::backward, &BUTTON_SET_1);
TextureBox forwardButton = TextureBox(
    (Vector2){buttonPos.x + (buttonDimension.x + buttonDistance.x) * 4,
              buttonPos.y},
    buttonDimension, (Rectangle){0, 0, 100, 100}, &mLib::forward,
    &BUTTON_SET_1);
TextureBox playButton = TextureBox(
    (Vector2){buttonPos.x + (buttonDimension.x + buttonDistance.x) * 2,
              buttonPos.y},
    buttonDimension, (Rectangle){0, 0, 100, 100}, &mLib::pause, &BUTTON_SET_1);
TextureBox pauseButton = TextureBox(
    (Vector2){buttonPos.x + (buttonDimension.x + buttonDistance.x) * 2,
              buttonPos.y},
    buttonDimension, (Rectangle){0, 0, 100, 100}, &mLib::expand, &BUTTON_SET_1);
TextureBox prevButton = TextureBox(
    (Vector2){buttonPos.x + (buttonDimension.x + buttonDistance.x),
              buttonPos.y},
    buttonDimension, (Rectangle){0, 0, 100, 100}, &mLib::prev, &BUTTON_SET_1);
TextureBox nextButton = TextureBox(
    (Vector2){buttonPos.x + (buttonDimension.x + buttonDistance.x) * 3,
              buttonPos.y},
    buttonDimension, (Rectangle){0, 0, 100, 100}, &mLib::next, &BUTTON_SET_1);
Button showMenu = Button(optionPosition,
                         (Vector2){sliderBarDimension.y, sliderBarDimension.x},
                         ">", 20, &BUTTON_SET_1);
Button clearButton = Button(optionPosition, sliderBarDimension, "Clear", 20,
                            AppMenu::buttonPalette);
Button importButton = Button(optionPosition, sliderBarDimension, "Import", 20,
                             AppMenu::buttonPalette);
Button randomButton = Button(optionPosition, sliderBarDimension, "Random", 20,
                             AppMenu::buttonPalette);
InsertBox insertBox = InsertBox(optionPosition, optionDimension, 20,
                                AppMenu::buttonPalette, 0, MaxSizeNum);
edgeInsertBox edgeBox =
    edgeInsertBox(optionPosition, optionDimension, 20, AppMenu::buttonPalette,
                  0, MaxSizeNum, MaxSizeWeight);
std::string requestText = "";
std::string requestNum = "";
std::vector<std::string> requestEdge = {"", "", ""};
bool showMenuFlag = false, requestClear = false, requestImport = false,
     requestRandom = false, inAnimationProcess = false, isPlaying = true;
std::vector<std::pair<Button*, Type>> GUIObjects = {};
// * For menu panes
MenuPane basePane({optionPosition.x + 10 + showMenu.getDimension().x,
                   optionPosition.y},
                  &GBLight::BACKGROUND1, &BUTTON_SET_1, &BUTTON_SET_1);
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

    // minValue = 1.f, maxValue = 100.f, sliderValue = 50.f;

    MaxSizeNum = 3, MaxSizeText = 5, MaxSizeWeight = 5;

    // clearButton = Button(optionPosition, sliderBarDimension, "Clear", 20,
    //                      AppMenu::buttonPalette);
    // importButton = Button(optionPosition, sliderBarDimension, "Import", 20,
    //                       AppMenu::buttonPalette);
    // randomButton = Button(optionPosition, sliderBarDimension, "Random", 20,
    //                       AppMenu::buttonPalette);
    // insertBox = InsertBox(optionPosition, optionDimension, 20,
    //                       AppMenu::buttonPalette, 0, MaxSizeNum);
    // edgeBox =
    //     edgeInsertBox(optionPosition, optionDimension, 20,
    //                   AppMenu::buttonPalette, 0, MaxSizeNum, MaxSizeWeight);
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
    requestText = "";
    requestNum = "";
    requestEdge = {"", "", ""};
    showMenuFlag = false, requestClear = false, requestImport = false,
    requestRandom = false, inAnimationProcess = false, isPlaying = true;
    GUIObjects = {};
}

void init() {
    clearButton.disable();
    importButton.disable();
    randomButton.disable();
    pauseButton.disable();
    playButton.enable();
}

void CLEAR() {
    requestText = "";
    requestNum = "";
    requestEdge = {"", "", ""};
    sliderValue = 50.f;
    showMenuFlag = false;
    GUIObjects.clear();
}

void pack(Button* obj, Type type) {
    std::cout << "pack" << std::endl;
    if (obj == nullptr) return;
    std::cout << "pack 1" << std::endl;
    obj->setPosition(
        (Vector2){optionPosition.x + showMenu.getDimension().x,
                  optionPosition.y + optionDimension.y * GUIObjects.size()});
    obj->setDimension(optionDimension);
    GUIObjects.push_back(std::make_pair(obj, type));
    showMenu.setDimension(
        (Vector2){optionDimension.y, optionDimension.y * GUIObjects.size()});
}

void render() {
    handleInput();
    showMenu.render();
    if (showMenuFlag) {
        // std::cout << GUIObjects.size() << std::endl;
        basePane.render();
        if (addPane) addPane->render();
        if (deletePane) deletePane->render();
        if (algoPane) algoPane->render();
        if (storagePane) storagePane->render();
        // for (auto &obj : GUIObjects) {
        //     if (obj.first != nullptr) {
        //         obj.first->render();
        //         if (obj.first->isOpen() && inAnimationProcess == false) {
        //             if (obj.second == EdgeInsert)
        //                 requestEdge = edgeBox.render();
        //             else if (obj.second == NumInsert)
        //                 requestNum = insertBox.render();
        //             else if (obj.second == TextInsert)
        //                 requestText = insertBox.render();
        //             else if (obj.second == CREATE) {
        //                 clearButton.render();
        //                 importButton.render();
        //                 randomButton.render();
        //                 if (clearButton.isPressed()) {
        //                     requestClear = true;
        //                     requestImport = false;
        //                     requestRandom = false;
        //                 } else if (importButton.isPressed()) {
        //                     requestImport = true;
        //                     requestClear = false;
        //                     requestRandom = false;
        //                 } else if (randomButton.isPressed()) {
        //                     requestRandom = true;
        //                     requestImport = false;
        //                     requestClear = false;
        //                 }
        //             }  // else assert(Type::None != obj.second);
        // }
        // }
        // }
    }
    backwardButton.render();
    forwardButton.render();

    pauseButton.render();
    playButton.render();
    prevButton.render();
    nextButton.render();
    ///* Slider bar **/
    GuiSliderBar(
        (Rectangle){
            sliderBarPos.x + sliderBarDimension.x,
            sliderBarPos.y + sliderBarDimension.y + sliderBarDimension.y / 2,
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

        // Button *object = nullptr;
        // Type type = None;
        // for (auto &obj : GUIObjects)
        //     if (obj.first != nullptr) {
        //         if (obj.first->isPressed()) {
        //             object = obj.first;
        //             type = obj.second;
        //             break;
        //         }
        //     }
        // if (object != nullptr) {
        //     for (auto &obj : GUIObjects)
        //         if (obj.first != nullptr && obj.first != object &&
        //             obj.first->isOpen())
        //             obj.first->changeOpen();
        //     object->changeOpen();
        //     init();
        //     if (object->isOpen()) {
        //         if (type == CREATE) {
        //             requestClear = false;
        //             requestImport = false;
        //             requestRandom = false;
        //             clearButton.enable();
        //             importButton.enable();
        //             randomButton.enable();
        //             clearButton = Button(
        //                 (Vector2){optionPosition.x +
        //                 showMenu.getDimension().x +
        //                               object->getDimension().x,
        //                           object->getPosition().y},
        //                 optionDimension, "Clear", 20,
        //                 AppMenu::buttonPalette);
        //             importButton = Button(
        //                 (Vector2){optionPosition.x +
        //                 showMenu.getDimension().x +
        //                               object->getDimension().x,
        //                           object->getPosition().y +
        //                           optionDimension.y},
        //                 optionDimension, "Import", 20,
        //                 AppMenu::buttonPalette);
        //             randomButton = Button(
        //                 (Vector2){
        //                     optionPosition.x + showMenu.getDimension().x +
        //                         object->getDimension().x,
        //                     object->getPosition().y + optionDimension.y * 2},
        //                 optionDimension, "Random", 20,
        //                 AppMenu::buttonPalette);
        //         } else if (type == EdgeInsert) {
        //             requestEdge = {"", "", ""};
        //             edgeBox = edgeInsertBox(
        //                 (Vector2){optionPosition.x +
        //                 showMenu.getDimension().x +
        //                               object->getDimension().x,
        //                           object->getPosition().y},
        //                 optionDimension, 20, AppMenu::buttonPalette, 0,
        //                 MaxSizeNum, MaxSizeWeight);
        //         } else if (type == NumInsert) {
        //             requestText = "";
        //             requestNum = "";
        //             insertBox = InsertBox(
        //                 (Vector2){optionPosition.x +
        //                 showMenu.getDimension().x +
        //                               object->getDimension().x,
        //                           object->getPosition().y},
        //                 optionDimension, 20, AppMenu::buttonPalette, 0,
        //                 MaxSizeNum);
        //         } else if (type == TextInsert) {
        //             requestText = "";
        //             requestNum = "";
        //             insertBox = InsertBox(
        //                 (Vector2){optionPosition.x +
        //                 showMenu.getDimension().x +
        //                               object->getDimension().x,
        //                           object->getPosition().y},
        //                 optionDimension, 20, AppMenu::buttonPalette, 1,
        //                 MaxSizeText);
        //         }  // else assert(Type::None != type);
        //     }
        // }
    }

    if (playButton.isPressed()) {
        Loop::isRunning = false;
        playButton.disable();
        pauseButton.enable();
    } else
        if (pauseButton.isPressed()) {
        Loop::isRunning = true;
        pauseButton.disable();
        playButton.enable();
    }
};

};  // namespace MenuTable
