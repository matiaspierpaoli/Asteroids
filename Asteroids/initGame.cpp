#include "initGame.h"
#include "raylib.h"
#include <vector>
#include "player.h"
#include "shoot.h"
#include "header.h"

void initGame(Screen& screen)
{
	screen = Screen::menu; // Set first screen as menu

	Player* player;
	vector<Shoot*> shoot;
	vector<Meteor*> smallMeteor;
	vector<Meteor*> mediumMeteor;
	vector<Meteor*> bigMeteor;

	float posX;
	float posY;

	int smallMeteorCounter;
	int mediumMeteorCounter;
	int bigMeteorCounter;

	int maxSmallMeteorCounter = 16;
	int maxMediumMeteorCounter = 8;
	int maxBigMeteorCounter = 4;

	int meteorsDestroyedCounter = 0;

	bool correctRangeMeteors = false;
	bool isGameOver = false;
	bool victory = false;

	player = new Player();

	for (int i = 0; i < maxBigMeteorCounter; i++)
	{
		posX = GetRandomValue(0, screenWidth);
		
		while (!correctRangeMeteors)
		{
			if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
			else correctRangeMeteors = true;
		}

		correctRangeMeteors = false;

		posY = GetRandomValue(0, screenHeight);

		while (!correctRangeMeteors)
		{
			if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150) posY = GetRandomValue(0, screenHeight);
			else correctRangeMeteors = true;
		}
		correctRangeMeteors = false;
	}

	for (int i = 0; i < mediumMeteorCounter; i++)
	{
		posX = GetRandomValue(0, screenWidth);

		while (!correctRangeMeteors)
		{
			if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
			else correctRangeMeteors = true;
		}

		correctRangeMeteors = false;

		posY = GetRandomValue(0, screenHeight);

		while (!correctRangeMeteors)
		{
			if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150) posY = GetRandomValue(0, screenHeight);
			else correctRangeMeteors = true;
		}
		correctRangeMeteors = false;
	}

	for (int i = 0; i < smallMeteorCounter; i++)
	{
		posX = GetRandomValue(0, screenWidth);

		while (!correctRangeMeteors)
		{
			if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
			else correctRangeMeteors = true;
		}

		correctRangeMeteors = false;

		posY = GetRandomValue(0, screenHeight);

		while (!correctRangeMeteors)
		{
			if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150) posY = GetRandomValue(0, screenHeight);
			else correctRangeMeteors = true;
		}
		correctRangeMeteors = false;
	}


	InitWindow(screenWidth, screenHeight, "Asteroids");

	SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

}