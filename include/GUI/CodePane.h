#pragma once
#include <vector>

#include "button.h"
#include "colorPalette.h"
#include "form.h"
#include "textbox.h"

namespace CodePane {
// Render info
extern Vector2 codeBlockPosition;
extern Vector2 codeLineSize;
extern ColorSet const *codeBlockColor;

extern Vector2 buttonDimension;
extern ColorSet const *buttonPalette;
extern Vector2 panelPosition;

extern bool isDarkMode;
extern Button backButton;

extern Button colorModeButton;
extern int horizontalCellCount;
extern int verticalCellCount;

extern Vector2 buttonDistance;
// Buttons
// Forms
// For rendering objects
extern std::vector<GUIObject *> renderList;
extern std::vector<TextBox> codeList;
extern int* highlightValue;

void init();

void render();

void loadCode(const std::vector<std::string> &strVect);
void setHighlight(int *index);
}  // namespace AppMenu