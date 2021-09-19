#include "drawGame.h"
#include "raylib.h"
#include "header.h"
#include "player.h"
#include "meteors.h"

void drawGame(Screen& screen, bool& gameOver, bool pause, int framesCounter, const int maxSmallMeteorCounter, const int maxMediumMeteorCounter, const int maxBigMeteorCounter, Player* player, Meteors* smallMeteor, Meteors* mediumMeteor, Meteors* bigMeteor)
{
    BeginDrawing();

    ClearBackground(BLACK);

    if (!gameOver)
    {
        // Draw spaceship
        Vector2 v1 = { player->position.x + sinf(player->rotation * DEG2RAD) * (player->height), player->position.y - cosf(player->rotation * DEG2RAD) * (player->height) };
        Vector2 v2 = { player->position.x - cosf(player->rotation * DEG2RAD) * (player->size / 2), player->position.y - sinf(player->rotation * DEG2RAD) * (player->size / 2) };
        Vector2 v3 = { player->position.x + cosf(player->rotation * DEG2RAD) * (player->size / 2), player->position.y + sinf(player->rotation * DEG2RAD) * (player->size / 2) };
        DrawTriangle(v1, v2, v3, RED);

        // Draw meteor
        for (int i = 0; i < maxSmallMeteorCounter; i++)
        {
            if (smallMeteor[i].active) DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, DARKGRAY);
            else DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
        }

        for (int i = 0; i < maxMediumMeteorCounter; i++)
        {
            if (mediumMeteor[i].active) DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, GRAY);
            else DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
        }
        
        for (int i = 0; i < maxBigMeteorCounter; i++)
        {
            if (bigMeteor[i].active) DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, DARKGRAY);
            else DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
        }
       

        DrawText(TextFormat("TIME: %.02f", (float)framesCounter / 60), 10, 10, 20, BLACK);

        if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
    }
    else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

    EndDrawing();


}