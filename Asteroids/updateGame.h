#pragma once
#include "header.h"
#include "player.h"
#include "meteors.h"

void updateGame(bool& gameOver, bool& pause, int& framesCounter, float PLAYER_SPEED, Player* player, Meteors* smallMeteor, Meteors* mediumMeteor, Meteors* bigMeteor, Screen& screen, int maxSmallMeteorCounter, int maxMediumMeteorCounter, int maxBigMeteorCounter);
