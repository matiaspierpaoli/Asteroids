#pragma once
#include "header.h"
#include "player.h"
#include "meteors.h"

void drawGame(Screen& screen, bool& gameOver, bool pause, int framesCounter, const int maxSmallMeteorCounter, const int maxMediumMeteorCounter, const int maxBigMeteorCounter, Player* player, Meteors* smallMeteor, Meteors* mediumMeteor, Meteors* bigMeteor);