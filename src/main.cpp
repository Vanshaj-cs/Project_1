#include <iostream>
#include "raylib.h"

using namespace std;

const int screenWidth = 800;
const int screenHeight = 600;

typedef struct Player {
    Vector2 position;
    Vector2 velocity;
    float width;
    float height;
    bool onGround;
} Player;

int main(){
    InitWindow(screenWidth, screenHeight, "Neon Depths - Prototype 1.0");
    SetTargetFPS(60);

    Player player = { { 100, 400 }, { 0, 0 }, 32, 48, false };

    const float gravity = 800.0f;
    const float jumpForce = -350.0f;
    const float moveSpeed = 200.0f;

    while(WindowShouldClose() == false){

        float deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_LEFT)) player.velocity.x = -moveSpeed;
        else if (IsKeyDown(KEY_RIGHT)) player.velocity.x = moveSpeed;
        else player.velocity.x = 0;

        if (IsKeyPressed(KEY_SPACE) && player.onGround) {
            player.velocity.y = jumpForce;
            player.onGround = false;
        }

        player.velocity.y += gravity * deltaTime;
        player.position.x += player.velocity.x * deltaTime;
        player.position.y += player.velocity.y * deltaTime;

        if (player.position.y + player.height >= screenHeight - 50) {
            player.position.y = screenHeight - 50 - player.height;
            player.velocity.y = 0;
            player.onGround = true;
        }

        BeginDrawing();  
        ClearBackground(BLACK);

         DrawRectangle(0, screenHeight - 50, screenWidth, 50, DARKGRAY);


         DrawRectangle((int)player.position.x, (int)player.position.y, player.width, player.height, BLACK);
         DrawRectangleLinesEx((Rectangle){player.position.x, player.position.y, player.width, player.height}, 2, SKYBLUE);
 
         DrawText("NEON DEPTHS", 10, 10, 20, DARKPURPLE);
 
        EndDrawing();
    }
}