#include "game.h"
#include "header.h"
#include "menu.h"
#include "credits.h"
#include "howToPlay.h"
#include "runGame.h"

void runGame(Screen& screen)
{
	initGame(screen);

	while (!WindowShouldClose())
	{
		switch (screen)
		{
		case Screen::menu:
			menu(screen);
			break;
		case Screen::game:
			game(screen);
			break;
		case Screen::howToPlay:
			howToPlay(screen);
			break;
		case Screen::credits:
			credits(screen);
			break;
		case Screen::close:	
			unloadGame();
			CloseWindow();		
			break;
		default:
			break;
		}
	}


}