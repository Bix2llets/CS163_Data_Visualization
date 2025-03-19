#pragma once
#include <vector>

#include "button.h"
#include "colorPalette.h"
#include "form.h"
#include "textbox.h"

namespace AppMenu {
// Render info
extern Vector2 codeBlockPosition;
extern Vector2 codeLineSize;
extern ColorSet codeBlockColor;

extern Vector2 buttonDimension;
extern ColorSet buttonPalette;
extern Vector2 panelPosition;

extern int horizontalCellCount;
extern int verticalCellCount;

// Buttons
extern std::vector<std::vector<Button>> buttonPanel;
extern Button backButton;
extern Button undoButton;
extern Button redoButton;
extern Button togglePauseButton;
// Forms
extern Form locationBox;
extern Form valueBox;

extern TextBox locationText;
extern TextBox valueText;
// For rendering objects
extern std::vector<GUIObject *> renderList;
extern std::vector<TextBox> codeList;
extern int* highlightValue;

void init();

void render();

void loadCode(const std::vector<std::string> &strVect);
}  // namespace AppMenu