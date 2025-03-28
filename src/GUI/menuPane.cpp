#include "menuPane.h"

const Vector2 MenuPane::FORM_DIMENSION = {160, 20};
const Vector2 MenuPane::ELEMENT_DISTANCE = {30, 30};
const Vector2 MenuPane::FORM_DIMENSION = {100, 25};
const Vector2 MenuPane::EDGE_OFFSET = {5, 5};

void MenuPane::set(bool newState) {
    enabled = newState;

    for (Button &button: btnList) button.set(newState);
    for (std::vector<Form> &formList: formList)
        for (Form &form: formList) 
            form.set(newState);
}

void MenuPane::enable() {
    set(true);
}

void MenuPane::disable() {
    set(false);
}

void MenuPane::toggle() {
    set(!enabled);
}

void MenuPane::render() {
    if (!enabled) return;
    if (btnList.size() == 0) return;
    Vector2 backgroundDimension = Vector2Scale(EDGE_OFFSET, 2);
    backgroundDimension.y += btnList.size() * (ELEMENT_DISTANCE.y + std::max(BUTTON_DIMENSION.y, FORM_DIMENSION.y)) - ELEMENT_DISTANCE.y; 
    
    int maxForm = 0;
    for (auto &formRow: formList) maxForm = std::max(maxForm, int(formRow.size()));

    backgroundDimension.x += BUTTON_DIMENSION.x;
    backgroundDimension.x += (FORM_DIMENSION.x + ELEMENT_DISTANCE.x) * maxForm;

    DrawRectangleV(STARTING_POSITION, backgroundDimension, *background);
}