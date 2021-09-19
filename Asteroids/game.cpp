#include "game.h"
#include "initGame.h"
#include "updateDrawFrame.h"

void game(Screen& screen)
{
	initGame(screen);

	while (!WindowShouldClose())
	{
		updateDrawFrame();
	}	
}