#include "SLLScene.h"

float SLLScene::stepDelay = 0.f;
float SLLScene::timeLeft = 0.f;

const Rectangle SLLScene::CANVAS = {50, 50, 1500, 550};
float SLLScene::animationRate = 1.0f;
SLL SLLScene::sll(CANVAS, animationRate);

void SLLScene::addEnd() {};
void SLLScene::addAt(int place) {};
void SLLScene::deleteEnd() {};
void SLLScene::deleteAt(int place) {};
void SLLScene::update() {};
