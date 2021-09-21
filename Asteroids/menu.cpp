#include "raylib.h"
#include "header.h"

void menu(Screen& screen)
{
	Rectangle playButton;
	playButton.x = GetScreenWidth() / 2 - 60;
	playButton.y = GetScreenHeight() / 2;
	playButton.height = 30;
	playButton.width = 79;

	Rectangle howToPlay;
	howToPlay.x = GetScreenWidth() / 2 - 100;
	howToPlay.y = GetScreenHeight() / 2 + 50;
	howToPlay.height = 30;
	howToPlay.width = 180;

	Rectangle creditsButton;
	creditsButton.x = GetScreenWidth() / 2 - 76;
	creditsButton.y = GetScreenHeight() / 2 + 100;
	creditsButton.height = 30;
	creditsButton.width = 113;

	Rectangle closeButton;
	closeButton.x = GetScreenWidth() / 2 - 66;
	closeButton.y = GetScreenHeight() / 2 + 150;
	closeButton.height = 30;
	closeButton.width = 81;

	while (!WindowShouldClose() && screen == Screen::menu)
	{
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(FormatText("Asteroids"), GetScreenWidth() / 2 - 300, GetScreenHeight() / 8, 120, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), playButton)) DrawText(FormatText("Play"), playButton.x, playButton.y, 30, RED);
		else  DrawText(FormatText("Play"), playButton.x, playButton.y, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), howToPlay)) DrawText(FormatText("How to play"), howToPlay.x, playButton.y + 50, 30, RED);
		else  DrawText(FormatText("How to play"), howToPlay.x, playButton.y + 50, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), creditsButton)) DrawText(FormatText("Credits"), creditsButton.x, creditsButton.y, 30, RED);
		else  DrawText(FormatText("Credits"), creditsButton.x, creditsButton.y, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), closeButton)) DrawText(FormatText("Close"), closeButton.x, closeButton.y, 30, RED);
		else  DrawText(FormatText("Close"), closeButton.x, closeButton.y, 30, WHITE);


		if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) screen = Screen::game;
		if (CheckCollisionPointRec(GetMousePosition(), howToPlay) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) screen = Screen::howToPlay;
		if (CheckCollisionPointRec(GetMousePosition(), creditsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) screen = Screen::credits;
		if (CheckCollisionPointRec(GetMousePosition(), closeButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) screen = Screen::close;


		EndDrawing();

	}

}