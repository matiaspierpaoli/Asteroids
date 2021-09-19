#include "updateDrawFrame.h"
#include "drawGame.h"
#include "updateGame.h"

void updateDrawFrame()
{
	updateGame();
	drawGame();

}