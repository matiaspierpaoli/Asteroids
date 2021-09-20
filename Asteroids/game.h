#pragma once
#include "header.h"
#include "player.h"
#include "meteors.h"

static Screen screen;

void game(Screen& screen);

int runGame(Screen& screen);
void drawGame(bool& gameOver, bool pause, int framesCounter, const int maxSmallMeteorCounter, const int maxMediumMeteorCounter, const int maxBigMeteorCounter);
void updateGame(bool& gameOver, bool& pause, int& framesCounter, float PLAYER_SPEED, int maxSmallMeteorCounter, int maxMediumMeteorCounter, int maxBigMeteorCounter);
void updateDrawFrame(bool& gameOver, bool& pause, int& framesCounter, float PLAYER_SPEED, int maxSmallMeteorCounter, int maxMediumMeteorCounter, int maxBigMeteorCounter);
void initGame(Screen& screenId);
void resetGame();