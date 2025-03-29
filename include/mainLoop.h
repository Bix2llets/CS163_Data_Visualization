#pragma once
#include "appMenu.h"
#include "raylib.h"
#include "singlyLInkedList.h"
#include "edgeInsertBox.hpp"

// Component scenes 
#include "SLLScene.h"
#include "welcomeMenu.h"
namespace Loop {
    enum SceneList { MAIN_MENU, LINKED_LIST, TRIE, GRAPH, AVL, HASH };
extern float elapsedSinceLastUpdate;
extern int frameCount;
extern const float DELTA_TIME;
extern SceneList currentScene;
extern bool isRunning;

extern const Vector2 UPPER_LEFT;
extern const Vector2 LOWER_RIGHT;

extern edgeInsertBox edgeBox;

extern void (*renderFunc)();
extern void (*updateFunc)();
extern void (*recordFunc)();

void registerInput();
void update();
void render();
void checkForReturn();

}  // namespace Loop