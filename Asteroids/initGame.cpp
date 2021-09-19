#include "initGame.h"
#include "raylib.h"
#include <vector>
#include "player.h"
#include "shoot.h"
#include "header.h"
#include "meteors.h"

void initGame(Screen& screen)
{
	screen = Screen::menu; // Set first screen as menu

	const int maxSmallMeteorCounter = 16;
	const int maxMediumMeteorCounter = 8;
	const int maxBigMeteorCounter = 4;

	Player* player;
	vector<Shoot*> shoot;
	Meteors* smallMeteor[maxSmallMeteorCounter] = { 0 };
	Meteors* mediumMeteor[maxMediumMeteorCounter] = { 0 };
	Meteors* bigMeteor[maxBigMeteorCounter] = { 0 };

	float posX;
	float posY;

	float velX;
	float velY;

	int smallMeteorCounter;
	int mediumMeteorCounter;
	int bigMeteorCounter;

	const float meteorsSpeed = 2.0f;

	int meteorsDestroyedCounter = 0;
	int framesCounter = 0;

	bool correctRangeMeteors = false;
	bool isGameOver = false;
	bool victory = false;
	bool pause = false;

	//player = new Player();

	player->speed = Vector2{ 0, 0 };
	player->acceleration = 0;
	player->rotation = 0;	
	player->color = RED;
	player->size = 20.0f;
	player->height = (player->size / 2) / tanf(20 * DEG2RAD);
	player->position = Vector2{ screenWidth / 2, screenHeight / 2 - player->height / 2 };
	player->collider = Vector3{ player->position.x + sin(player->rotation * DEG2RAD) * (player->height / 2.5f), player->position.y - cos(player->rotation * DEG2RAD) * (player->height / 2.5f), 12 };

	for (int i = 0; i < maxMediumMeteorCounter; i++)
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
			if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
			else correctRangeMeteors = true;
		}

		correctRangeMeteors = false;
		velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
		velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

		while (!correctRangeMeteors)
		{
			if (velX == 0 && velY == 0)
			{
				velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
				velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
			}
			else correctRangeMeteors = true;
		}
		mediumMeteor[i]->position = Vector2{ posX, posY };
		mediumMeteor[i]->speed = Vector2{ velX, velY };
		mediumMeteor[i]->radius = 20;
		mediumMeteor[i]->active = true;
		mediumMeteor[i]->color = GREEN;
	}

	for (int i = 0; i < maxSmallMeteorCounter; i++)
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
			if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
			else correctRangeMeteors = true;
		}

		correctRangeMeteors = false;
		velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
		velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

		while (!correctRangeMeteors)
		{
			if (velX == 0 && velY == 0)
			{
				velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
				velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
			}
			else correctRangeMeteors = true;
		}
		smallMeteor[i]->position = Vector2{ posX, posY };
		smallMeteor[i]->speed = Vector2{ velX, velY };
		smallMeteor[i]->radius = 10;
		smallMeteor[i]->active = true;
		smallMeteor[i]->color = YELLOW;
	}

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
			if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
			else correctRangeMeteors = true;
		}

		correctRangeMeteors = false;
		velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
		velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);

		while (!correctRangeMeteors)
		{
			if (velX == 0 && velY == 0)
			{
				velX = GetRandomValue(-meteorsSpeed, meteorsSpeed);
				velY = GetRandomValue(-meteorsSpeed, meteorsSpeed);
			}
			else correctRangeMeteors = true;
		}
		bigMeteor[i]->position = Vector2{ posX, posY };
		bigMeteor[i]->speed = Vector2{ velX, velY };
		bigMeteor[i]->radius = 30;
		bigMeteor[i]->active = true;
		bigMeteor[i]->color = BLUE;
	}


	InitWindow(screenWidth, screenHeight, "Asteroids");

	SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

}