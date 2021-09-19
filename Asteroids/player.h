#pragma once
#include "raylib.h"

class Player
{
private:
	int playerX;
	int playerY;	
	float playerSpeed;
	float playerRadius;

public:

	Player();
	void update();



};