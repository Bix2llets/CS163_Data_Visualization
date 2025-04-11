#pragma once
#include "appMenu.h"
#include "raylib.h"

#include "menu.hpp"

// Component scenes 
#include "SLLScene.h"
#include "graphScene.h"
#include "AVLScene.h"
#include "hashScene.h"
#include "trieScene.h"
#include "welcomeMenu.h"
namespace Loop {
    enum SceneList { MAIN_MENU, LINKED_LIST, TRIE, GRAPH, AVL, HASH };
extern float elapsedSinceLastUpdate;
extern int frameCount;

extern SceneList currentScene;
extern bool isRunning;


extern void (*renderFunc)();
extern void (*updateFunc)();
extern void (*recordFunc)();

void configSlider();
void setColorPalette();
void registerInput();
void update();
void render();
void checkForReturn();

}  // namespace Loop