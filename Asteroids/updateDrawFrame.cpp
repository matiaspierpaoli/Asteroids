#include "updateDrawFrame.h"
#include "drawGame.h"
#include "updateGame.h"
#include "player.h"
#include "meteors.h"
#include "header.h"

void updateDrawFrame(bool& gameOver, bool& pause, int& framesCounter, float PLAYER_SPEED, Player* player, Meteors* smallMeteor, Meteors* mediumMeteor, Meteors* bigMeteor, Screen& screen, int maxSmallMeteorCounter, int maxMediumMeteorCounter, int maxBigMeteorCounter)
{
	updateGame(gameOver, pause, framesCounter, PLAYER_SPEED, player, smallMeteor,  mediumMeteor,  bigMeteor, screen, maxSmallMeteorCounter, maxMediumMeteorCounter, maxBigMeteorCounter);
	drawGame(screen, gameOver,pause, framesCounter, maxSmallMeteorCounter, maxMediumMeteorCounter, maxBigMeteorCounter, player,  smallMeteor, mediumMeteor, bigMeteor);

	
}