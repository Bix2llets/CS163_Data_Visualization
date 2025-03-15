#pragma once
#include <vector>

#include "button.h"
#include "colorPalette.h"
#include "form.h"
#include "textbox.h"
enum class SceneList { MAIN_MENU, LINKED_LIST, TRIE, GRAPH, HASH };
namespace AppMenu {
extern Vector2 codeBlockPosition;
extern Vector2 codeLineSize;
extern ColorSet codeBlockColor;

extern Vector2 buttonDimension;
extern ColorSet buttonPalette;
extern Button addByValueButton;
extern Button addAtIndexButton;
extern Button addButton;

extern Button removeByValueButton;
extern Button removeAtIndexButton;
extern Button removeButton;

extern Form locationBox;
extern Form valueBox;

extern std::vector<GUIObject *> renderList;
extern std::vector<TextBox> codeList;

void init();

void render();

void loadCode(const std::vector<std::string> &strVect);
}  // namespace AppMenu