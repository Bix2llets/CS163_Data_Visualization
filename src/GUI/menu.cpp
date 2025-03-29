#include "menu.hpp"
#include "raygui.h"
namespace MenuTable
{
    Vector2 optionPosition = {10, 600};
    Vector2 optionDimension = {200, 50};
    
    Vector2 sliderBarPos = {500, 400};
    Vector2 sliderBarDimension = {50, 50};

    float minValue = 1.f, maxValue = 100.f, sliderValue = 50.f;
    
    int MaxSizeNum = 3, MaxSizeText = 5, MaxSizeWeight = 5;
    TextureBox backwardButton = TextureBox(sliderBarPos, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::backward, "", 20, AppMenu::buttonPalette);
    TextureBox forwardButton = TextureBox((Vector2){sliderBarPos.x + sliderBarDimension.x * 4, sliderBarPos.y}, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::forward, "", 20, AppMenu::buttonPalette);
    TextureBox playButton = TextureBox((Vector2){sliderBarPos.x + sliderBarDimension.x * 2, sliderBarPos.y}, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::play, "", 20, AppMenu::buttonPalette);
    TextureBox pauseButton = TextureBox((Vector2){sliderBarPos.x + sliderBarDimension.x * 2, sliderBarPos.y}, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::pause, "", 20, AppMenu::buttonPalette);
    TextureBox prevButton = TextureBox((Vector2){sliderBarPos.x + sliderBarDimension.x, sliderBarPos.y}, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::prev, "", 20, AppMenu::buttonPalette);
    TextureBox nextButton = TextureBox((Vector2){sliderBarPos.x + sliderBarDimension.x * 3, sliderBarPos.y}, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::next, "", 20, AppMenu::buttonPalette);
    Button showMenu = Button(optionPosition, (Vector2){sliderBarDimension.y, sliderBarDimension.x}, ">", 20, AppMenu::buttonPalette);
    Button clearButton = Button(optionPosition, sliderBarDimension, "Clear", 20, AppMenu::buttonPalette);
    Button importButton = Button(optionPosition, sliderBarDimension, "Import", 20, AppMenu::buttonPalette);
    Button randomButton = Button(optionPosition, sliderBarDimension, "Random", 20, AppMenu::buttonPalette);
    InsertBox insertBox = InsertBox(optionPosition, optionDimension, 20, AppMenu::buttonPalette, 0, MaxSizeNum);
    edgeInsertBox edgeBox = edgeInsertBox(optionPosition, optionDimension, 20, AppMenu::buttonPalette, 0, MaxSizeNum, MaxSizeWeight);
    std::string requestText = "";
    std::string requestNum = "";
    std::vector<std::string> requestEdge = {"", "", ""};
    bool showMenuFlag = false, requestClear = false, requestImport = false, requestRandom = false, inAnimationProcess = false, isPlaying = true;
    std::vector<std::pair<Button *, Type>> GUIObjects = {};
    
    void Constructor(Vector2 _optionPosition = {10, 600}, Vector2 _optionDimension = {200, 50}, 
        Vector2 _sliderBarPos = {500, 400}, Vector2 _sliderBarDimension = {50, 50}) {
        optionPosition = _optionPosition;
        optionDimension = _optionDimension;
        sliderBarPos = _sliderBarPos;
        sliderBarDimension = _sliderBarDimension;

        minValue = 1.f, maxValue = 100.f, sliderValue = 50.f;
        
        MaxSizeNum = 3, MaxSizeText = 5, MaxSizeWeight = 5;
        backwardButton = TextureBox(sliderBarPos, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::backward, "", 20, AppMenu::buttonPalette);
        forwardButton = TextureBox((Vector2){sliderBarPos.x + sliderBarDimension.x * 4, sliderBarPos.y}, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::forward, "", 20, AppMenu::buttonPalette);
        playButton = TextureBox((Vector2){sliderBarPos.x + sliderBarDimension.x * 2, sliderBarPos.y}, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::play, "", 20, AppMenu::buttonPalette);
        pauseButton = TextureBox((Vector2){sliderBarPos.x + sliderBarDimension.x * 2, sliderBarPos.y}, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::pause, "", 20, AppMenu::buttonPalette);
        prevButton = TextureBox((Vector2){sliderBarPos.x + sliderBarDimension.x, sliderBarPos.y}, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::prev, "", 20, AppMenu::buttonPalette);
        nextButton = TextureBox((Vector2){sliderBarPos.x + sliderBarDimension.x * 3, sliderBarPos.y}, sliderBarDimension, (Rectangle){0, 0, 100, 100}, mLib::next, "", 20, AppMenu::buttonPalette);
        showMenu = Button(optionPosition, (Vector2){sliderBarDimension.y, sliderBarDimension.x}, ">", 20, AppMenu::buttonPalette);
        clearButton = Button(optionPosition, sliderBarDimension, "Clear", 20, AppMenu::buttonPalette);
        importButton = Button(optionPosition, sliderBarDimension, "Import", 20, AppMenu::buttonPalette);
        randomButton = Button(optionPosition, sliderBarDimension, "Random", 20, AppMenu::buttonPalette);
        insertBox = InsertBox(optionPosition, optionDimension, 20, AppMenu::buttonPalette, 0, MaxSizeNum);
        edgeBox = edgeInsertBox(optionPosition, optionDimension, 20, AppMenu::buttonPalette, 0, MaxSizeNum, MaxSizeWeight);
        requestText = "";
        requestNum = "";
        requestEdge = {"", "", ""};
        showMenuFlag = false, requestClear = false, requestImport = false, requestRandom = false, inAnimationProcess = false, isPlaying = true;
        GUIObjects = {};   
    }

    void init() {
        clearButton.disable();
        importButton.disable();
        randomButton.disable();
    }

    void CLEAR() {
        requestText = "";
        requestNum = "";
        requestEdge = {"", "", ""};
        sliderValue = 50.f;
        showMenuFlag = false;
        GUIObjects.clear();
    }
    
    void pack(Button *obj, Type type) {
        std::cout << "pack" << std::endl;
        if (obj == nullptr) return;
        std::cout << "pack 1" << std::endl;
        obj->setPosition((Vector2){optionPosition.x + showMenu.getDimension().x, optionPosition.y + optionDimension.y * GUIObjects.size()});
        obj->setDimension(optionDimension);
        GUIObjects.push_back(std::make_pair(obj, type));
        showMenu.setDimension((Vector2){optionDimension.y, optionDimension.y * GUIObjects.size()});
    }
    
    void render() {
        handleInput();
        showMenu.render();
        if (showMenuFlag) {
            std::cout << GUIObjects.size() << std::endl;
            for (auto &obj : GUIObjects) {
                if (obj.first != nullptr) {
                    obj.first->render();
                    if (obj.first->isOpen() && inAnimationProcess == false) {
                        if (obj.second == EdgeInsert) requestEdge = edgeBox.render();
                        else if (obj.second == NumInsert) requestNum = insertBox.render();
                        else if (obj.second == TextInsert) requestText = insertBox.render();
                        else if (obj.second == CREATE) {
                            clearButton.render();
                            importButton.render();
                            randomButton.render();
                            if (clearButton.isPressed()) {
                                requestClear = true;
                                requestImport = false;
                                requestRandom = false;
                            } else if (importButton.isPressed()) {
                                requestImport = true;
                                requestClear = false;
                                requestRandom = false;
                            } else if (randomButton.isPressed()) {
                                requestRandom = true;
                                requestImport = false;
                                requestClear = false;
                            }
                        } //else assert(Type::None != obj.second);
                    }
                }
            }
        }
        backwardButton.render();
        forwardButton.render();
        if (isPlaying) pauseButton.render();
        else playButton.render();
        prevButton.render();
        nextButton.render(); 
        ///* Slider bar **/
            GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, ColorToInt(AppMenu::buttonPalette.borderNormal));
            GuiSetStyle(SLIDER, BORDER_COLOR_FOCUSED, ColorToInt(AppMenu::buttonPalette.borderNormal));
            GuiSetStyle(SLIDER, BORDER_COLOR_PRESSED, ColorToInt(AppMenu::buttonPalette.borderNormal));
            GuiSetStyle(SLIDER, BORDER_WIDTH, 2);
            GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, ColorToInt(AppMenu::buttonPalette.backgroundNormal));
            GuiSetStyle(SLIDER, BASE_COLOR_FOCUSED, ColorToInt(AppMenu::buttonPalette.backgroundHighlight));
            GuiSetStyle(SLIDER, BASE_COLOR_PRESSED, ColorToInt(AppMenu::buttonPalette.backgroundHighlight));
            GuiSetStyle(SLIDER, TEXT_COLOR_NORMAL, ColorToInt(AppMenu::buttonPalette.textNormal));
            GuiSetStyle(SLIDER, TEXT_COLOR_FOCUSED, ColorToInt(AppMenu::buttonPalette.textHighlight));
            GuiSetStyle(SLIDER, TEXT_COLOR_PRESSED, ColorToInt(AppMenu::buttonPalette.textHighlight));
            GuiSetStyle(DEFAULT, TEXT_SIZE, DrawUtility::NORMAL_SIZE);
            GuiSetFont(DrawUtility::inter20);
        ///

        GuiSliderBar((Rectangle){sliderBarPos.x + sliderBarDimension.x, sliderBarPos.y + sliderBarDimension.y + sliderBarDimension.y / 2, sliderBarDimension.x * 3, sliderBarDimension.y / 2}, "Time Step", TextFormat("%.2f", sliderValue), &sliderValue, minValue, maxValue);
    }
    
    void handleInput() {
        if (showMenu.isPressed()) {
            showMenuFlag = !showMenuFlag;
        }
        if (showMenuFlag) showMenu.setText("<");
        else showMenu.setText(">");
        if (showMenuFlag) {
            Button *object = nullptr;
            Type type = None;
            for (auto &obj : GUIObjects) 
                if (obj.first != nullptr) {
                    if (obj.first->isPressed()) {
                        object = obj.first;
                        type = obj.second;
                        break ;
                    } 
                }
            if (object != nullptr) {
                for (auto &obj : GUIObjects)
                    if (obj.first != nullptr && obj.first != object && obj.first->isOpen()) obj.first->changeOpen();
                object->changeOpen(); 
                init();
                if (object->isOpen()) {
                    if (type == CREATE) {
                        requestClear = false;
                        requestImport = false;
                        requestRandom = false;
                        clearButton.enable();
                        importButton.enable();
                        randomButton.enable();
                        clearButton = Button((Vector2){optionPosition.x + showMenu.getDimension().x + object->getDimension().x, object->getPosition().y}, 
                        optionDimension, "Clear", 20, AppMenu::buttonPalette);
                        importButton = Button((Vector2){optionPosition.x + showMenu.getDimension().x + object->getDimension().x, object->getPosition().y + optionDimension.y},
                        optionDimension, "Import", 20, AppMenu::buttonPalette);
                        randomButton = Button((Vector2){optionPosition.x + showMenu.getDimension().x + object->getDimension().x, object->getPosition().y + optionDimension.y * 2},
                        optionDimension, "Random", 20, AppMenu::buttonPalette);
                    } else if (type == EdgeInsert) {
                        requestEdge = {"", "", ""};
                        edgeBox = edgeInsertBox((Vector2){optionPosition.x + showMenu.getDimension().x + object->getDimension().x, object->getPosition().y}
                        , optionDimension, 20, AppMenu::buttonPalette, 0, MaxSizeNum, MaxSizeWeight);
                    } else if (type == NumInsert) {
                        requestText = "";
                        requestNum = "";
                        insertBox = InsertBox((Vector2){optionPosition.x + showMenu.getDimension().x + object->getDimension().x, object->getPosition().y}
                        , optionDimension, 20, AppMenu::buttonPalette, 0, MaxSizeNum);
                    } else if (type == TextInsert) {
                        requestText = "";
                        requestNum = "";
                        insertBox = InsertBox((Vector2){optionPosition.x + showMenu.getDimension().x + object->getDimension().x, object->getPosition().y}
                        , optionDimension, 20, AppMenu::buttonPalette, 1, MaxSizeText);
                    } //else assert(Type::None != type);
                }
            }
        }
    };

};    

