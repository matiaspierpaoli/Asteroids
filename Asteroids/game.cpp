#include "game.h"
#include "menu.h"

#define PLAYER_BASE_SIZE  20.0f
#define METEORS_SPEED    1.5f
float PLAYER_SPEED = 3.0f;


const int maxSmallMeteorCounter = 10;
const int maxMediumMeteorCounter = 6;
const int maxBigMeteorCounter = 3;
const int maxPlayerShoots = 10;

static float shipHeight = 0.0f;

static Player player = { 0 };
static Meteors smallMeteor[maxSmallMeteorCounter] = { 0 };
static Meteors mediumMeteor[maxMediumMeteorCounter] = { 0 };
static Meteors bigMeteor[maxBigMeteorCounter] = { 0 };
static Shoot shoot[maxPlayerShoots] = { 0 };

int framesCounter = 0;

Vector2 posNave;
Vector2 posMouse;
Vector2 vectorDirection;
Vector2 normalizedDirection;

float angle = 0;

static int midMeteorsCount = 0;
static int smallMeteorsCount = 0;
static int destroyedMeteorsCount = 0;

bool correctRangeMeteors = false;
bool gameOver = false;
bool victory = false;
bool pause = false;


void game(Screen& screen)
{	
	updateDrawFrame(gameOver, pause, framesCounter, PLAYER_SPEED, maxSmallMeteorCounter, maxMediumMeteorCounter, maxBigMeteorCounter);
	
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
		for (int i = 0; i < maxBigMeteorCounter; i++)
		{
			if (bigMeteor[i].active) DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, RED);
		}

		for (int i = 0; i < maxMediumMeteorCounter; i++)
		{
			if (mediumMeteor[i].active) DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, YELLOW);
		}

		for (int i = 0; i < maxSmallMeteorCounter; i++)
		{
			if (smallMeteor[i].active) DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, GREEN);
		}

		// Draw shoot
		for (int i = 0; i < maxPlayerShoots; i++)
		{
			if (shoot[i].active) DrawCircleV(shoot[i].position, shoot[i].radius, RED);
		}

		if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);

		if (victory) DrawText("VICTORY", screenWidth / 2 - MeasureText("VICTORY", 20) / 2, screenHeight / 2, 20, LIGHTGRAY);

		DrawText(TextFormat("TIME: %.02f", (float)framesCounter / 60), 10, 10, 20, WHITE);

	}
	else
	{				
		DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 20) / 2, screenHeight / 2, 20, LIGHTGRAY);
		DrawText("Press ENTER to return to menu", GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 20, WHITE);							
	}

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

			if (framesCounter == 30 * 60)
			{
				victory = true;
			}

			player.collider = Vector3{ player.position.x + sin(player.rotation * DEG2RAD) * (player.height / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (player.height / 2.5f), 12 };

			if (!CheckCollisionPointCircle(GetMousePosition(), player.position, player.collider.z))
			{
				//posNave = player.position;

				// Player logic

				// Rotation   

				posMouse = GetMousePosition(); // Get destination position

				vectorDirection = { posMouse.x - player.position.x , posMouse.y - player.position.y }; // Subtact two vectors

				angle = atan2f(vectorDirection.y, vectorDirection.x) * (180.0f / PI); // Calculate arc tangent

				// Add degrees to the position the ship is watching
				if (vectorDirection.y > 0 && vectorDirection.x > 0) angle += 90.0f;
				else if (vectorDirection.y > 0 && vectorDirection.x < 0) angle += 90.0f;
				else if (vectorDirection.y < 0 && vectorDirection.x > 0) angle += 90.0f;
				else angle += 90.0f;

				player.rotation = angle; // Define rotation as the angle calculated before

				// Speed
				player.speed.x = sin(player.rotation * DEG2RAD) * PLAYER_SPEED;
				player.speed.y = cos(player.rotation * DEG2RAD) * PLAYER_SPEED;

				normalizedDirection = vectorDirection;
				//sumar aceleracion en esa direccion
				//player.acceleration += (vectorDirection.x + vectorDirection.y);
				//player.acceleration += normalizedDirection;

				/*player.acceleration.x += {vectorDirection.x, vectorDirection.y};
				player.acceleration.y += vectorDirection;*/


				// Movement 
				/*player.newPosition.x = posNave.x + player.acceleration.x;
				player.newPosition.y = posNave.y + player.acceleration.y;*/

				//// Movement
				//player.position.x += player.acceleration.x;
				//player.position.y -= player.acceleration.y;

				// Movement
				/*player.position.x += (player.speed.x * player.acceleration);
				player.position.y -= (player.speed.y * player.acceleration);*/

				/*if (!CheckCollisionPointCircle(GetMousePosition(), player.position, player.collider.z))
				{
					if (IsKeyPressed(MOUSE_LEFT_BUTTON))
					{

						player.position.x += (player.speed.x * player.acceleration) * 2;
						player.position.y -= (player.speed.y * player.acceleration) * 2;

					}
					else
					{

						player.position.x += (player.speed.x * player.acceleration);
						player.position.y -= (player.speed.y * player.acceleration);
					}



				}*/
				if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
				{
					player.position.x += (player.speed.x * player.acceleration) * 2;
					player.position.y -= (player.speed.y * player.acceleration) * 2;
				}
				else
				{
					player.position.x += (player.speed.x * player.acceleration);
					player.position.y -= (player.speed.y * player.acceleration);
				}

			}






			// Movement
			/*if (!CheckCollisionPointCircle(GetMousePosition(), player.position, player.collider.z))
			{

			}*/


			// Wall behaviour for player
			if (player.position.x > screenWidth + player.height) player.position.x = -(player.height);
			else if (player.position.x < -(player.height)) player.position.x = screenWidth + player.height;
			else if (player.position.y > (screenHeight + player.height)) player.position.y = -(player.height);
			else if (player.position.y < -(player.height)) player.position.y = screenHeight + player.height;

			/*if (player.position.x >= screenWidth)
			{
				player.position.x = -(player.height);
			}
			else if (player.position.x <= 0)
			{
				player.position.x = screenWidth + player.height;
			}
			else if (player.position.y >= screenHeight)
			{
				player.position.y = -(player.height);
			}
			else if (player.position.y <= 0)
			{
				player.position.y = screenHeight + player.height;
			}*/



			// Meteor logic

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				for (int i = 0; i < maxPlayerShoots; i++)
				{
					if (!shoot[i].active)
					{
						shoot[i].position = Vector2{ player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight), player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight) };
						shoot[i].active = true;
						shoot[i].speed.x = 1.5 * sin(player.rotation * DEG2RAD) * PLAYER_SPEED;
						shoot[i].speed.y = 1.5 * cos(player.rotation * DEG2RAD) * PLAYER_SPEED;
						shoot[i].rotation = player.rotation;
						break;
					}
				}
			}




			// Shoot life timer
			for (int i = 0; i < maxPlayerShoots; i++)
			{
				if (shoot[i].active) shoot[i].lifeSpawn++;
			}

			// Shot logic
			for (int i = 0; i < maxPlayerShoots; i++)
			{
				if (shoot[i].active)
				{
					// Movement
					shoot[i].position.x += shoot[i].speed.x;
					shoot[i].position.y -= shoot[i].speed.y;

					// Collision logic: shoot vs walls
					if (shoot[i].position.x > screenWidth + shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					else if (shoot[i].position.x < 0 - shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					if (shoot[i].position.y > screenHeight + shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					else if (shoot[i].position.y < 0 - shoot[i].radius)
					{
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}

					// Life of shoot
					if (shoot[i].lifeSpawn >= 60)
					{
						shoot[i].position = Vector2{ 0, 0 };
						shoot[i].speed = Vector2{ 0, 0 };
						shoot[i].lifeSpawn = 0;
						shoot[i].active = false;
					}
				}
			}

			// Collision logic: player vs meteors
			player.collider = Vector3{ player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight / 2.5f), 12 };

			for (int a = 0; a < maxBigMeteorCounter; a++)
			{
				if (CheckCollisionCircles(Vector2 { player.collider.x, player.collider.y }, player.collider.z, bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active) gameOver = true;
			}

			for (int a = 0; a < maxMediumMeteorCounter; a++)
			{
				if (CheckCollisionCircles(Vector2 { player.collider.x, player.collider.y }, player.collider.z, mediumMeteor[a].position, mediumMeteor[a].radius) && mediumMeteor[a].active) gameOver = true;
			}

			for (int a = 0; a < maxSmallMeteorCounter; a++)
			{
				if (CheckCollisionCircles(Vector2 { player.collider.x, player.collider.y }, player.collider.z, smallMeteor[a].position, smallMeteor[a].radius) && smallMeteor[a].active) gameOver = true;
			}

			// Meteors logic: big meteors
			for (int i = 0; i < maxBigMeteorCounter; i++)
			{
				if (bigMeteor[i].active)
				{
					// Movement
					bigMeteor[i].position.x += bigMeteor[i].speed.x;
					bigMeteor[i].position.y += bigMeteor[i].speed.y;

					// Collision logic: meteor vs wall
					if (bigMeteor[i].position.x > screenWidth + bigMeteor[i].radius) bigMeteor[i].position.x = -(bigMeteor[i].radius);
					else if (bigMeteor[i].position.x < 0 - bigMeteor[i].radius) bigMeteor[i].position.x = screenWidth + bigMeteor[i].radius;
					if (bigMeteor[i].position.y > screenHeight + bigMeteor[i].radius) bigMeteor[i].position.y = -(bigMeteor[i].radius);
					else if (bigMeteor[i].position.y < 0 - bigMeteor[i].radius) bigMeteor[i].position.y = screenHeight + bigMeteor[i].radius;
				}
			}

			// Meteors logic: medium meteors
			for (int i = 0; i < maxMediumMeteorCounter; i++)
			{
				if (mediumMeteor[i].active)
				{
					// Movement
					mediumMeteor[i].position.x += mediumMeteor[i].speed.x;
					mediumMeteor[i].position.y += mediumMeteor[i].speed.y;

					// Collision logic: meteor vs wall
					if (mediumMeteor[i].position.x > screenWidth + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
					else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = screenWidth + mediumMeteor[i].radius;
					if (mediumMeteor[i].position.y > screenHeight + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
					else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = screenHeight + mediumMeteor[i].radius;
				}
			}

			// Meteors logic: small meteors
			for (int i = 0; i < maxSmallMeteorCounter; i++)
			{
				if (smallMeteor[i].active)
				{
					// Movement
					smallMeteor[i].position.x += smallMeteor[i].speed.x;
					smallMeteor[i].position.y += smallMeteor[i].speed.y;

					// Collision logic: meteor vs wall
					if (smallMeteor[i].position.x > screenWidth + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
					else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = screenWidth + smallMeteor[i].radius;
					if (smallMeteor[i].position.y > screenHeight + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
					else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = screenHeight + smallMeteor[i].radius;
				}
			}

			// Collision logic: player-shoots vs meteors
			for (int i = 0; i < maxPlayerShoots; i++)
			{
				if ((shoot[i].active))
				{
					for (int a = 0; a < maxBigMeteorCounter; a++)
					{
						if (bigMeteor[a].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, bigMeteor[a].position, bigMeteor[a].radius))
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							bigMeteor[a].active = false;
							destroyedMeteorsCount++;

							for (int j = 0; j < 2; j++)
							{
								if (midMeteorsCount % 2 == 0)
								{
									mediumMeteor[midMeteorsCount].position = Vector2{ bigMeteor[a].position.x, bigMeteor[a].position.y };
									mediumMeteor[midMeteorsCount].speed = Vector2{ cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1, sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1 };
								}
								else
								{
									mediumMeteor[midMeteorsCount].position = Vector2{ bigMeteor[a].position.x, bigMeteor[a].position.y };
									mediumMeteor[midMeteorsCount].speed = Vector2{ cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED, sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED };
								}

								mediumMeteor[midMeteorsCount].active = true;
								midMeteorsCount++;
							}
							//bigMeteor[a].position = (Vector2){-100, -100};
							bigMeteor[a].color = RED;
							a = maxBigMeteorCounter;
						}
					}

					for (int b = 0; b < maxMediumMeteorCounter; b++)
					{
						if (mediumMeteor[b].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, mediumMeteor[b].position, mediumMeteor[b].radius))
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							mediumMeteor[b].active = false;
							destroyedMeteorsCount++;

							for (int j = 0; j < 2; j++)
							{
								if (smallMeteorsCount % 2 == 0)
								{
									smallMeteor[smallMeteorsCount].position = Vector2{ mediumMeteor[b].position.x, mediumMeteor[b].position.y };
									smallMeteor[smallMeteorsCount].speed = Vector2{ cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1, sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED * -1 };
								}
								else
								{
									smallMeteor[smallMeteorsCount].position = Vector2{ mediumMeteor[b].position.x, mediumMeteor[b].position.y };
									smallMeteor[smallMeteorsCount].speed = Vector2{ cos(shoot[i].rotation * DEG2RAD) * METEORS_SPEED, sin(shoot[i].rotation * DEG2RAD) * METEORS_SPEED };
								}

								smallMeteor[smallMeteorsCount].active = true;
								smallMeteorsCount++;
							}
							//mediumMeteor[b].position = (Vector2){-100, -100};
							mediumMeteor[b].color = GREEN;
							b = maxMediumMeteorCounter;
						}
					}

					for (int c = 0; c < maxSmallMeteorCounter; c++)
					{
						if (smallMeteor[c].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, smallMeteor[c].position, smallMeteor[c].radius))
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							smallMeteor[c].active = false;
							destroyedMeteorsCount++;
							smallMeteor[c].color = YELLOW;
							// smallMeteor[c].position = (Vector2){-100, -100};
							c = maxSmallMeteorCounter;
						}
					}
				}
			}
		}

		if (destroyedMeteorsCount == maxBigMeteorCounter + maxMediumMeteorCounter + maxSmallMeteorCounter) victory = true;
	}
	else
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			runGame(screen);			
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

	const float meteorsSpeed = 1.5f;

	gameOver = false;
	victory = false;

	framesCounter = 0;

	/*int meteorsDestroyedCounter = 0;*/
	

	shipHeight = (PLAYER_BASE_SIZE / 2) / tanf(20 * DEG2RAD);

	player.position = Vector2{ screenWidth / 2, screenHeight / 2 - shipHeight / 2 };
	player.speed = Vector2{ 0, 0 };
	player.acceleration = 1;
	player.rotation = 0;
	player.collider = Vector3{ player.position.x + sin(player.rotation * DEG2RAD) * (shipHeight / 2.5f), player.position.y - cos(player.rotation * DEG2RAD) * (shipHeight / 2.5f), 12 };
	player.color = LIGHTGRAY;

	destroyedMeteorsCount = 0;

	for (int i = 0; i < maxPlayerShoots; i++)
	{
		shoot[i].position = Vector2{ 0, 0 };
		shoot[i].speed = Vector2{ 0, 0 };
		shoot[i].radius = 2;
		shoot[i].active = false;
		shoot[i].lifeSpawn = 0;
		shoot[i].color = WHITE;
	}

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