#include "level.h"
#include "globals.h"

int level[MAP_HEIGHT][MAP_WIDTH] = {
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 0
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 1
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 2
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 3
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 4
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 5
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 6
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 7
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 8
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 9
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 10
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 11
    { 1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0 }, // 12 
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, // 13
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }  // 14 = ground
};

void DrawLevel() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (level[y][x] == 1) {
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKPURPLE);
                DrawRectangleLinesEx((Rectangle){x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE}, 1, VIOLET);
            }
        }
    }
}

void CheckPlayerCollision(Player &player) {
    float dt = GetFrameTime(); // Use consistent dt

    Rectangle playerRect = {player.position.x, player.position.y, player.width, player.height};
    player.onGround = false;

    // Move X
    player.position.x += player.velocity.x * dt;
    playerRect.x = player.position.x;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (level[y][x] == 1) {
                Rectangle tileRect = {(float)x * TILE_SIZE, (float)y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                if (CheckCollisionRecs(playerRect, tileRect)) {
                    if (player.velocity.x > 0) {
                        player.position.x = tileRect.x - player.width;
                    } else if (player.velocity.x < 0) {
                        player.position.x = tileRect.x + tileRect.width;
                    }
                    player.velocity.x = 0;
                    playerRect.x = player.position.x;
                }
            }
        }
    }

    // Move Y
    player.position.y += player.velocity.y * dt;
    playerRect.y = player.position.y;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (level[y][x] == 1) {
                Rectangle tileRect = {(float)x * TILE_SIZE, (float)y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                if (CheckCollisionRecs(playerRect, tileRect)) {
                    if (player.velocity.y > 0) {
                        // Landing
                        player.position.y = tileRect.y - player.height;
                        player.onGround = true;
                    } else if (player.velocity.y < 0) {
                        // Ceiling hit
                        player.position.y = tileRect.y + tileRect.height;
                    }
                    player.velocity.y = 0;
                    playerRect.y = player.position.y;
                }
            }
        }
    }
}