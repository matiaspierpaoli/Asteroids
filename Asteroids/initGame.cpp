#include "initGame.h"
#include "raylib.h"

void initGame(Screen& screen)
{
	screen = Screen::menu; // Set first screen as menu

	// Set window's width and height
	const int screenWidth = 800;
	const int screenHeight = 400;

	InitWindow(screenWidth, screenHeight, "Asteroids");

	SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

}