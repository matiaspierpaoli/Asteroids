#include "credits.h"


void credits(Screen& screen)
{
	while (!WindowShouldClose() && screen == Screen::credits)
	{
		BeginDrawing();

		ClearBackground(BLACK);
		DrawText(FormatText("Made by: Matias Pierpaoli"), GetScreenWidth() / 2 - 175, GetScreenHeight() / 2, 30, RED);
		DrawText("Press ESC to return to menu", GetScreenWidth() / 2 - 150, GetScreenHeight() - 50, 20, RED);

		EndDrawing();
	}

	screen = Screen::menu;

}