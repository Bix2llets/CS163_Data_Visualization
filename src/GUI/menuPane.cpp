#include "menuPane.h"

const Vector2 MenuPane::BUTTON_DIMENSION = {100, 20};
const Vector2 MenuPane::ELEMENT_DISTANCE = {30, 30};
const Vector2 MenuPane::FORM_DIMENSION = {100, 20};
const Vector2 MenuPane::EDGE_OFFSET = {5, 25};

void MenuPane::set(bool newState) {
    enabled = newState;

    for (Button &button : btnList) button.set(newState);
    for (std::vector<Form> &formList : formList)
        for (Form &form : formList) form.set(newState);
}

void MenuPane::enable() { set(true); }

void MenuPane::disable() { set(false); }

void MenuPane::toggle() { set(!enabled); }

void MenuPane::render() {
    if (!enabled) return;
    if (btnList.size() == 0) return;

    // * Drawing background
    Vector2 backgroundDimension = Vector2Scale(EDGE_OFFSET, 2);
    backgroundDimension.y +=
        btnList.size() * (ELEMENT_DISTANCE.y +
                          std::max(BUTTON_DIMENSION.y, FORM_DIMENSION.y)) -
        ELEMENT_DISTANCE.y;

    int maxForm = 0;
    for (auto &formRow : formList)
        maxForm = std::max(maxForm, int(formRow.size()));

    backgroundDimension.x += BUTTON_DIMENSION.x;
    backgroundDimension.x += (FORM_DIMENSION.x + ELEMENT_DISTANCE.x) * maxForm;

    // DrawRectangleV(STARTING_POSITION, backgroundDimension, *background);

    DrawRectangleRounded({STARTING_POSITION.x, STARTING_POSITION.y, backgroundDimension.x, backgroundDimension.y}, 0.3f, 10, *background);
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
}

void MenuPane::newLine(int row, int numberOfForms,
                       const std::string &buttonLabel,
                       const std::vector<std::string> &titleList) {
    if (row + 1 > btnList.size()) {
        btnList.resize(row + 1);
        formList.resize(row + 1);
        formTitleList.resize(row + 1);
    }

    formList[row].clear();
    formTitleList[row].clear();

    Vector2 startingPoint = Vector2Add(STARTING_POSITION, EDGE_OFFSET);
    startingPoint.y += row * (std::max(BUTTON_DIMENSION.y, FORM_DIMENSION.y) +
                              ELEMENT_DISTANCE.y);
    btnList[row] = Button(startingPoint, BUTTON_DIMENSION, buttonLabel, 16,
                          buttonPalette, &DrawUtility::inter16);

    for (int i = 0; i < numberOfForms; i++) {
        formList[row].push_back(
            Form({startingPoint.x + BUTTON_DIMENSION.x + ELEMENT_DISTANCE.x +
                      i * (FORM_DIMENSION.x + ELEMENT_DISTANCE.x),
                  startingPoint.y, FORM_DIMENSION.x, FORM_DIMENSION.y},
                 formPalette));
    }

    for (int i = 0; i < numberOfForms; i++) {
        if (i < titleList.size())
            formTitleList[row].push_back(titleList[i]);
        else
            formTitleList[row].push_back("");
    }
}

std::string MenuPane::getText(int row, int col) {
    if (row >= formList.size()) return "";
    if (col >= formList[row].size()) return "";
    return formList[row][col].getText();
}

bool MenuPane::getPressed(int row) {
    if (row > btnList.size()) return false;
    return btnList[row].isPressed();
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