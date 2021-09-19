#include "updateGame.h"
#include "header.h"
#include "player.h"
#include "initGame.h"
#include "meteors.h"
#include "menu.h"

void updateGame(bool& gameOver, bool& pause, int& framesCounter, float PLAYER_SPEED, Player* player, Meteors* smallMeteor, Meteors* mediumMeteor, Meteors* bigMeteor, Screen& screen, int maxSmallMeteorCounter, int maxMediumMeteorCounter, int maxBigMeteorCounter)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            framesCounter++;

            // Player logic

            // Rotation
            if (IsKeyDown(KEY_LEFT)) player->rotation -= 5;
            if (IsKeyDown(KEY_RIGHT)) player->rotation += 5;

            // Speed
            player->speed.x = sin(player->rotation * DEG2RAD) * PLAYER_SPEED;
            player->speed.y = cos(player->rotation * DEG2RAD) * PLAYER_SPEED;

            // Controller
            if (IsKeyDown(KEY_UP))
            {
                if (player->acceleration < 1) player->acceleration += 0.04f;
            }
            else
            {
                if (player->acceleration > 0) player->acceleration -= 0.02f;
                else if (player->acceleration < 0) player->acceleration = 0;
            }
            if (IsKeyDown(KEY_DOWN))
            {
                if (player->acceleration > 0) player->acceleration -= 0.04f;
                else if (player->acceleration < 0) player->acceleration = 0;
            }

            // Movement
            player->position.x += (player->speed.x * player->acceleration);
            player->position.y -= (player->speed.y * player->acceleration);

            // Wall behaviour for player
            if (player->position.x > screenWidth + player->height) player->position.x = -(player->height);
            else if (player->position.x < -(player->height)) player->position.x = screenWidth + player->height;
            if (player->position.y > (screenHeight + player->height)) player->position.y = -(player->height);
            else if (player->position.y < -(player->height)) player->position.y = screenHeight + player->height;

            // Collision Player to meteors
            player->collider = Vector3{ player->position.x + sin(player->rotation * DEG2RAD) * (player->height / 2.5f), player->position.y - cos(player->rotation * DEG2RAD) * (player->height / 2.5f), 12 };

            for (int i = 0; i < maxMediumMeteorCounter; i++)
            {
                if (CheckCollisionCircles(Vector2 { player->collider.x, player->collider.y }, player->collider.z, mediumMeteor[i].position, mediumMeteor[i].radius) && mediumMeteor[i].active) gameOver = true;
            }

            for (int i = 0; i < maxSmallMeteorCounter; i++)
            {
                if (CheckCollisionCircles(Vector2 { player->collider.x, player->collider.y }, player->collider.z, smallMeteor[i].position, smallMeteor[i].radius) && smallMeteor[i].active) gameOver = true;
            }

            // Meteor logic

            for (int i = 0; i < maxMediumMeteorCounter; i++)
            {
                if (mediumMeteor[i].active)
                {
                    // movement
                    mediumMeteor[i].position.x += mediumMeteor[i].speed.x;
                    mediumMeteor[i].position.y += mediumMeteor[i].speed.y;

                    // wall behaviour
                    if (mediumMeteor[i].position.x > screenWidth + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
                    else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = screenWidth + mediumMeteor[i].radius;
                    if (mediumMeteor[i].position.y > screenHeight + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
                    else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = screenHeight + mediumMeteor[i].radius;
                }
            }

            for (int i = 0; i < maxSmallMeteorCounter; i++)
            {
                if (smallMeteor[i].active)
                {
                    // movement
                    smallMeteor[i].position.x += smallMeteor[i].speed.x;
                    smallMeteor[i].position.y += smallMeteor[i].speed.y;

                    // wall behaviour
                    if (smallMeteor[i].position.x > screenWidth + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
                    else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = screenWidth + smallMeteor[i].radius;
                    if (smallMeteor[i].position.y > screenHeight + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
                    else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = screenHeight + smallMeteor[i].radius;
                }
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            initGame(screen);
            gameOver = false;
        }
        else if (IsKeyPressed(KEY_ESCAPE))
        {
            screen = Screen::menu;
            menu(screen);
        }
    }

}