#pragma once
#include "header.h"

static Screen screen;

// Set window's width and height
const int screenWidth = 800;
const int screenHeight = 400;

void game(Screen& screen);

int runGame(Screen& screen);
void drawGame(bool& gameFinished, bool& gameOver, bool pause, int framesCounter, const int maxSmallMeteorCounter, const int maxMediumMeteorCounter, const int maxBigMeteorCounter);
void updateGame(bool& gameFinished, bool& gameOver, bool& pause, int& framesCounter, float PLAYER_SPEED, int maxSmallMeteorCounter, int maxMediumMeteorCounter, int maxBigMeteorCounter);
void updateDrawFrame(bool& gameFinished, bool& gameOver, bool& pause, int& framesCounter, float PLAYER_SPEED, int maxSmallMeteorCounter, int maxMediumMeteorCounter, int maxBigMeteorCounter);
void initGame(Screen& screenId);
void resetGame();