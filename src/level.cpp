#include "level.h"
#include "globals.h"

int level[MAP_HEIGHT][MAP_WIDTH] = {
    // Same tile data as before
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
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
    Rectangle playerRect = {player.position.x, player.position.y, player.width, player.height};
    player.onGround = false;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (level[y][x] == 1) {
                Rectangle tileRect = {(float)x * TILE_SIZE, (float)y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                if (CheckCollisionRecs(playerRect, tileRect)) {
                    // Only handle vertical collision for now
                    if (player.velocity.y > 0) {
                        player.position.y = tileRect.y - player.height;
                        player.velocity.y = 0;
                        player.onGround = true;
                    }
                }
            }
        }
    }
}