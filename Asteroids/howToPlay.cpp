#include "raylib.h"
#include "header.h"

void howToPlay(Screen& screen)
{
	while (!WindowShouldClose() && screen == Screen::howToPlay)
	{
		BeginDrawing();

		ClearBackground(BLACK);
		DrawText(FormatText("Rules:"), 15, 30, 40, RED);

		DrawText(FormatText("Asteroids is a simple game where a ship must avoid crashing with tons of asteroids."), 15, 110, 19, RED);
		DrawText(FormatText("You are given the possibility to shoot to break this rocks into smaller pieces."), 15, 140, 19, RED);
		DrawText(FormatText("You win if you survive 30 seconds or break all asteroids."), 15, 170, 20, RED);
		DrawText(FormatText("Right mouse button to move - Left mouse button to shoot."), 15, 200, 20, RED);
		DrawText(FormatText("P to pause"), 15, 230, 20, RED);


		DrawText("Press ESC to return to menu", GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 20, RED);

		if (IsKeyDown(KEY_ESCAPE))
		{
			screen = Screen::menu;
		}

		EndDrawing();
	}
	screen = Screen::menu;
}