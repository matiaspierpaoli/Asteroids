#include "game.h"
#include "menu.h"

#define PLAYER_BASE_SIZE  20.0f
#define METEORS_SPEED       2
float PLAYER_SPEED = 6.0f;


const int maxSmallMeteorCounter = 16;
const int maxMediumMeteorCounter = 8;
const int maxBigMeteorCounter = 4;

// Set window's width and height
const int screenWidth = 800;
const int screenHeight = 400;

static float shipHeight = 0.0f;


static Player player = { 0 };
static Meteors smallMeteor[maxSmallMeteorCounter] = { 0 };
static Meteors mediumMeteor[maxMediumMeteorCounter] = { 0 };
static Meteors bigMeteor[maxBigMeteorCounter] = { 0 };

int framesCounter = 0;

bool correctRangeMeteors = false;
bool isGameOver = false;
bool victory = false;
bool pause = false;


void game(Screen& screen)
{
	initGame(screen);

	while (!WindowShouldClose())
	{
		updateDrawFrame(isGameOver,pause, framesCounter, PLAYER_SPEED, maxSmallMeteorCounter, maxMediumMeteorCounter, maxBigMeteorCounter);
	}	
}

void drawGame(bool& gameOver, bool pause, int framesCounter, const int maxSmallMeteorCounter, const int maxMediumMeteorCounter, const int maxBigMeteorCounter)
{
    BeginDrawing();

    ClearBackground(BLACK);

    if (!gameOver)
    {
        // Draw spaceship
        Vector2 v1 = { player.position.x + sinf(player.rotation * DEG2RAD) * (shipHeight), player.position.y - cosf(player.rotation * DEG2RAD) * (shipHeight) };
        Vector2 v2 = { player.position.x - cosf(player.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2), player.position.y - sinf(player.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2) };
        Vector2 v3 = { player.position.x + cosf(player.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2), player.position.y + sinf(player.rotation * DEG2RAD) * (PLAYER_BASE_SIZE / 2) };
        DrawTriangle(v1, v2, v3, RED);

        // Draw meteor
        for (int i = 0; i < maxSmallMeteorCounter; i++)
        {
            if (smallMeteor[i].active) DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, DARKGRAY);
            else DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
        }

        for (int i = 0; i < maxMediumMeteorCounter; i++)
        {
            if (mediumMeteor[i].active) DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, GRAY);
            else DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
        }

        for (int i = 0; i < maxBigMeteorCounter; i++)
        {
            if (bigMeteor[i].active) DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, BLUE);
            else DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
        }


        DrawText(TextFormat("TIME: %.02f", (float)framesCounter / 60), 10, 10, 20, WHITE);

        if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
    }
    else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

    EndDrawing();


}

void updateGame(bool& gameOver, bool& pause, int& framesCounter, float PLAYER_SPEED, int maxSmallMeteorCounter, int maxMediumMeteorCounter, int maxBigMeteorCounter)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            framesCounter++;

            // Player logic

            // Rotation
            if (IsKeyDown(KEY_LEFT)) player.rotation -= 5;
            if (IsKeyDown(KEY_RIGHT)) player.rotation += 5;

            // Speed
            player.speed.x = sin(player.rotation * DEG2RAD) * PLAYER_SPEED;
            player.speed.y = cos(player.rotation * DEG2RAD) * PLAYER_SPEED;

            // Controller
            //if (IsKeyDown(KEY_UP))
            //{
                if (player.acceleration < 1) player.acceleration += 0.04f;
            //}
            //else
            //{
                if (player.acceleration > 0) player.acceleration -= 0.02f;
                else if (player.acceleration < 0) player.acceleration = 0;
            //}
            //if (IsKeyDown(KEY_DOWN))
            //{
                if (player.acceleration > 0) player.acceleration -= 0.04f;
                else if (player.acceleration < 0) player.acceleration = 0;
            //}

            // Movement
            player.position.x += (player.speed.x * player.acceleration);
            player.position.y -= (player.speed.y * player.acceleration);

            // Wall behaviour for player
            if (player.position.x > screenWidth + player.height) player.position.x = -(player.height);
            else if (player.position.x < -(player.height)) player.position.x = screenWidth + player.height;
            if (player.position.y > (screenHeight + player.height)) player.position.y = -(player.height);
            else if (player.position.y < -(player.height)) player.position.y = screenHeight + player.height;

            // Collision Player to meteors
           /* player.collider = Vector3{ player.position.x + sin(player.rotation * DEG2RAD) * (player.height / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (player.height / 2.5f), 12 };

            for (int i = 0; i < maxMediumMeteorCounter; i++)
            {
                if (CheckCollisionCircles(Vector2{ player.collider.x, player.collider.y }, player.collider.z, mediumMeteor[i].position, mediumMeteor[i].radius) && mediumMeteor[i].active) gameOver = true;
            }

            for (int i = 0; i < maxSmallMeteorCounter; i++)
            {
                if (CheckCollisionCircles(Vector2{ player.collider.x, player.collider.y }, player.collider.z, smallMeteor[i].position, smallMeteor[i].radius) && smallMeteor[i].active) gameOver = true;
            }

			for (int i = 0; i < maxBigMeteorCounter; i++)
			{
				if (CheckCollisionCircles(Vector2{ player.collider.x, player.collider.y }, player.collider.z, bigMeteor[i].position, bigMeteor[i].radius) && bigMeteor[i].active) gameOver = true;
			}*/

            // Meteor logic

			for (int i = 0; i < maxSmallMeteorCounter; i++)
			{
				if (smallMeteor[i].active)
				{
					// movement
					smallMeteor[i].position.x += smallMeteor[i].speed.x;
					smallMeteor[i].position.y += smallMeteor[i].speed.y;

					// wall behaviour
					if (smallMeteor[i].position.x > screenWidth + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
					else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = screenWidth + smallMeteor[i].radius;
					if (smallMeteor[i].position.y > screenHeight + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
					else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = screenHeight + smallMeteor[i].radius;
				}
			}

            for (int i = 0; i < maxMediumMeteorCounter; i++)
            {
                if (mediumMeteor[i].active)
                {
                    // movement
                    mediumMeteor[i].position.x += mediumMeteor[i].speed.x;
                    mediumMeteor[i].position.y += mediumMeteor[i].speed.y;

                    // wall behaviour
                    if (mediumMeteor[i].position.x > screenWidth + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
                    else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = screenWidth + mediumMeteor[i].radius;
                    if (mediumMeteor[i].position.y > screenHeight + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
                    else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = screenHeight + mediumMeteor[i].radius;
                }
            }

           

			for (int i = 0; i < maxBigMeteorCounter; i++)
			{
				if (bigMeteor[i].active)
				{
					// movement
					bigMeteor[i].position.x += bigMeteor[i].speed.x;
					bigMeteor[i].position.y += bigMeteor[i].speed.y;

					// wall behaviour
					if (bigMeteor[i].position.x > screenWidth + bigMeteor[i].radius) bigMeteor[i].position.x = -(bigMeteor[i].radius);
					else if (bigMeteor[i].position.x < 0 - bigMeteor[i].radius) bigMeteor[i].position.x = screenWidth + bigMeteor[i].radius;
					if (bigMeteor[i].position.y > screenHeight + bigMeteor[i].radius) bigMeteor[i].position.y = -(bigMeteor[i].radius);
					else if (bigMeteor[i].position.y < 0 - bigMeteor[i].radius) bigMeteor[i].position.y = screenHeight + bigMeteor[i].radius;
				}
			}
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            gameOver = false;
            screen = Screen::game;
            runGame(screen);
        }
        else if (IsKeyPressed(KEY_ESCAPE))
        {
            screen = Screen::menu;
            menu(screen);
        }
    }

}

void updateDrawFrame(bool& gameOver, bool& pause, int& framesCounter, float PLAYER_SPEED, int maxSmallMeteorCounter, int maxMediumMeteorCounter, int maxBigMeteorCounter)
{
    updateGame(gameOver, pause, framesCounter, PLAYER_SPEED, maxSmallMeteorCounter, maxMediumMeteorCounter, maxBigMeteorCounter);
    drawGame(gameOver, pause, framesCounter, maxSmallMeteorCounter, maxMediumMeteorCounter, maxBigMeteorCounter);
}

void initGame(Screen& screen)
{
	screen = Screen::menu; // Set first screen as menu

	float posX;
	float posY;

	float velX;
	float velY;

	const float meteorsSpeed = 2.0f;

	

	/*int meteorsDestroyedCounter = 0;*/
	

	shipHeight = (PLAYER_BASE_SIZE / 2) / tanf(20 * DEG2RAD);

	player.position = Vector2{ screenWidth / 2, screenHeight / 2 - shipHeight / 2 };
	player.speed = Vector2{ 0, 0 };
	player.acceleration = 0;
	player.rotation = 0;
	player.collider = Vector3{ player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight / 2.5f), 12 };
	player.color = LIGHTGRAY;

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
		mediumMeteor[i].position = Vector2{ posX, posY };
		mediumMeteor[i].speed = Vector2{ velX, velY };
		mediumMeteor[i].radius = 20;
		mediumMeteor[i].active = true;
		mediumMeteor[i].color = GREEN;
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
		smallMeteor[i].position = Vector2{ posX, posY };
		smallMeteor[i].speed = Vector2{ velX, velY };
		smallMeteor[i].radius = 10;
		smallMeteor[i].active = true;
		smallMeteor[i].color = YELLOW;
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
		bigMeteor[i].position = Vector2{ posX, posY };
		bigMeteor[i].speed = Vector2{ velX, velY };
		bigMeteor[i].radius = 30;
		bigMeteor[i].active = true;
		bigMeteor[i].color = BLUE;
	}


	InitWindow(screenWidth, screenHeight, "Asteroids");

	SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

}

void resetGame()
{


	/*player.clear();
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
	}*/


}