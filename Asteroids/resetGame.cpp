#include "resetGame.h"
#include "player.h"
#include "meteors.h"

void resetGame(Player* player, int maxSmallMeteorCounter, int maxMediumMeteorCounter, int maxBigMeteorCounter)
{
	delete player;

	for (int i = 0; i < maxSmallMeteorCounter; i++)
	{
		delete smallMeteor;
	}

	for (int i = 0; i < maxMediumMeteorCounter; i++)
	{
		delete mediumMeteor;
	}

	for (int i = 0; i < maxBigMeteorCounter; i++)
	{
		delete bigMeteor;
	}

	
}