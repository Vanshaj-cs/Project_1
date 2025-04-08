#include "player.h"
#include "globals.h"

void InitPlayer(Player &player) {
    player.position = { 100, 100 };
    player.velocity = { 0, 0 };
    player.width = 32;
    player.height = 48;
    player.onGround = false;
}

void UpdatePlayer(Player &player, float dt) {
    const float gravity = 800.0f;
    const float jumpForce = -450.0f;
    const float moveSpeed = 200.0f;

    // Horizontal input
    if (IsKeyDown(KEY_LEFT)) player.velocity.x = -moveSpeed;
    else if (IsKeyDown(KEY_RIGHT)) player.velocity.x = moveSpeed;
    else player.velocity.x = 0;

    // Jump
    if (IsKeyPressed(KEY_SPACE) && player.onGround) {
        player.velocity.y = jumpForce;
        player.onGround = false;
    }

    // Apply gravity
    player.velocity.y += gravity * dt;
}    

void DrawPlayer(const Player &player) {
    DrawRectangle((int)player.position.x, (int)player.position.y, player.width, player.height, BLACK);
    DrawRectangleLinesEx((Rectangle){player.position.x, player.position.y, player.width, player.height}, 2, SKYBLUE);
}