#include "game.h"
#include "raylib.h"
#include "header.h"
#include "menu.h"
#include "credits.h"
#include "howToPlay.h"
#include "player.h"
#include <vector>
#include "shoot.h"
#include "meteors.h"

int runGame(Screen& screen)
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
			return 0;
		default:
			break;
		}
	}

}