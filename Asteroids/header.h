#pragma once
#include <iostream>
#include "raylib.h"
#include <math.h>
#include <vector>

using namespace std;

enum class Screen { menu, game, howToPlay, credits, close, finishedgame };

typedef struct Player {
    Vector2 position;
    Vector2 speed;
    float acceleration;
    float rotation;
    Vector3 collider;
    Color color;
    int height;
} Player;

typedef struct Meteors {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
    Color color;
} Meteors;

typedef struct Shoot {
    Vector2 position;
    Vector2 speed;
    float radius;
    float rotation;
    int lifeSpawn;
    bool active;
    Color color;
} Shoot;



