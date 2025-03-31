#include "menuPane.h"

const Vector2 MenuPane::BUTTON_DIMENSION = {100, 20};
const Vector2 MenuPane::ELEMENT_DISTANCE = {30, 30};
const Vector2 MenuPane::FORM_DIMENSION = {75, 20};
const Vector2 MenuPane::EDGE_OFFSET = {8, 25};
const Vector2 MenuPane::RANDOM_DIMENSION = {30, 30};

void MenuPane::set(bool newState) {
    enabled = newState;

    for (Button &button : btnList) button.set(newState);
    for (std::vector<mForm> &formList : formList)
        for (Form &form : formList) form.set(newState);
}

void MenuPane::enable() { set(true); }

void MenuPane::disable() { set(false); }

void MenuPane::toggle() { set(!enabled); }

void MenuPane::render() {
    if (!enabled) return;
    if (btnList.size() == 0) return;

    // * Drawing background

    // DrawRectangleV(position, backgroundDimension, *background);

    DrawRectangleRounded({position.x, position.y, dimension.x, dimension.y}, 0.3f, 10, *background);
    // * Rendering buttons

    for (Button &button : btnList) button.render();

    for (int row = 0; row < formList.size(); row++)
        for (int col = 0; col < formList[row].size(); col++) 
        {
            Form &form = formList[row][col];
            form.render();

            std::string &str = formTitleList[row][col];
            Vector2 drawingCoordinate = form.getPosition();
            drawingCoordinate.x += FORM_DIMENSION.x / 2;
            drawingCoordinate.y -= 10;

            DrawUtility::drawText(str, drawingCoordinate, DrawUtility::inter16, formPalette->textNormal, 16, DrawUtility::SPACING, VerticalAlignment::CENTERED, HorizontalAlignment::CENTERED);
        }

    for (int row = 0; row < diceButton.size(); row++) {
        if (haveRandom[row]) diceButton[row].render();
    }
}

void MenuPane::newLine(int row, int numberOfForms,
                       const std::string &buttonLabel,
                       const std::vector<std::string> &titleList, const std::vector<bool> &formMode, bool isRandom) {
    if (row + 1 > btnList.size()) {
        btnList.resize(row + 1);
        formList.resize(row + 1);
        formTitleList.resize(row + 1);
        haveRandom.resize(row + 1);
        diceButton.resize(row + 1);
    }

    formList[row].clear();
    formTitleList[row].clear();

    Vector2 startingPoint = Vector2Add(position, EDGE_OFFSET);
    startingPoint.y += row * (std::max(BUTTON_DIMENSION.y, FORM_DIMENSION.y) +
                              ELEMENT_DISTANCE.y);
    btnList[row] = Button(startingPoint, BUTTON_DIMENSION, buttonLabel, 16,
                          buttonPalette, &DrawUtility::inter16);

    for (int i = 0; i < numberOfForms; i++) {
        formList[row].push_back(
            mForm({startingPoint.x + BUTTON_DIMENSION.x + ELEMENT_DISTANCE.x +
                      i * (FORM_DIMENSION.x + ELEMENT_DISTANCE.x),
                  startingPoint.y, FORM_DIMENSION.x, FORM_DIMENSION.y},
                 formPalette, formMode[i]));
    }

    for (int i = 0; i < numberOfForms; i++) {
        if (i < titleList.size())
            formTitleList[row].push_back(titleList[i]);
        else
            formTitleList[row].push_back("");
    }

    if (isRandom) {
        haveRandom[row] = true;
        Vector2 dicePosition = Vector2Add(position, EDGE_OFFSET);
        float offset = (RANDOM_DIMENSION.y - BUTTON_DIMENSION.y) / 2; 
        dicePosition.x -= offset;
        dicePosition.y -= offset;
        dicePosition.y += row * (std::max(BUTTON_DIMENSION.y, FORM_DIMENSION.y) + ELEMENT_DISTANCE.y);
        dicePosition.x += BUTTON_DIMENSION.x + ELEMENT_DISTANCE.x + formList[row].size() * (ELEMENT_DISTANCE.x + FORM_DIMENSION.x);
        diceButton[row] = DiceButton(dicePosition, {RANDOM_DIMENSION.x, RANDOM_DIMENSION.y}, &BUTTON_SET_1);
    }
    else {
        haveRandom[row] = false;
    }

    dimension = Vector2Scale(EDGE_OFFSET, 2);
    dimension.y +=
        btnList.size() * (ELEMENT_DISTANCE.y +
                          std::max(BUTTON_DIMENSION.y, FORM_DIMENSION.y)) -
        ELEMENT_DISTANCE.y;

    float totalBehind = 0;

    for (int i = 0; i < formList.size(); i++) {
        totalBehind = std::max(totalBehind, haveRandom[i] * (RANDOM_DIMENSION.x + ELEMENT_DISTANCE.x) + formList[i].size() * (FORM_DIMENSION.x + ELEMENT_DISTANCE.x));
    }

    dimension.x += BUTTON_DIMENSION.x;
    dimension.x += totalBehind;

}

std::string MenuPane::getText(int row, int col) {
    if (row >= formList.size()) return "";
    if (col >= formList[row].size()) return "";
    return formList[row][col].getText();
}

bool MenuPane::isButtonPressed(int row) {
    if (row > btnList.size()) return false;
    return btnList[row].isPressed();
}

bool MenuPane::isRandomPressed(int row) {
    if (row > btnList.size()) return false;
    if (haveRandom[row] == false) return false;
    return diceButton[row].isPressed();
}

Form& MenuPane::getForm(int row, int col) {
    assert(row < formList.size());
    assert(col < formList[row].size());
    return formList[row][col];
}

Button& MenuPane::getButton(int row) {
    assert(row < btnList.size());
    return btnList[row];
}

Vector2 MenuPane::getDimension() {
    return dimension;
}
