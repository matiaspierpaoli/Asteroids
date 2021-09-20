#include "runGame.h"
#include "game.h"

/* Pierpaoli Matias
Practica Profesional 1: Desarrollo de Videojuegos 1
Asteroids*/

int main()
{

	InitWindow(screenWidth, screenHeight, "Asteroids");

	SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	runGame(screen);

	return 0;
}