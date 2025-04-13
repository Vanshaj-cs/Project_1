#include "level.h"
#include "globals.h"

#define MAX_PLATFORMS 300

typedef struct {
    Rectangle rect;
} Platform;

Platform platforms[MAX_PLATFORMS];
int platformCount = 0;
float platformWidth = TILE_SIZE * 2; // consistent size
float platformY = 450.0f; // fixed Y position (ground level)

void InitLevel() {
    platformCount = 0;
    float x = 0;

    // Pre-fill initial ground
    for (int i = 0; i < 20; i++) {
        platforms[platformCount++] = (Platform){ { x, platformY, platformWidth, TILE_SIZE } };
        x += platformWidth;
    }
}

void UpdateLevel(Player &player) {
    float screenRight = player.position.x + 800;

    float lastX = 0;
    if (platformCount > 0) {
        Platform last = platforms[platformCount - 1];
        lastX = last.rect.x + last.rect.width;
    }

    while (lastX < screenRight && platformCount < MAX_PLATFORMS) {
        bool makeGap = GetRandomValue(0, 100) < 20;

        if (makeGap) {
            const float MIN_GAP = TILE_SIZE * 1.5f;
            const float MAX_GAP = TILE_SIZE * 2.5f;
            float gapWidth = GetRandomValue((int)MIN_GAP, (int)MAX_GAP);
            lastX += gapWidth;
        }

        bool placedElevated = false;

        // 30% chance to spawn elevated platform
        if (GetRandomValue(0, 100) < 30) {
            int elevation = GetRandomValue(2, 4); // tiles higher
            float elevatedY = platformY - elevation * TILE_SIZE;

            platforms[platformCount++] = (Platform){
                { lastX, elevatedY, platformWidth, TILE_SIZE }
            };
            placedElevated = true;
        }

        // Only place ground if no elevated platform above it
        if (!placedElevated) {
            platforms[platformCount++] = (Platform){
                { lastX, platformY, platformWidth, TILE_SIZE }
            };
        }

        lastX += platformWidth;
    }
}    
void DrawLevel() {
    for (int i = 0; i < platformCount; i++) {
        DrawRectangleRec(platforms[i].rect, DARKPURPLE);
        DrawRectangleLinesEx(platforms[i].rect, 1, VIOLET);
    }
}

void CheckPlayerCollision(Player &player) {
    float dt = GetFrameTime();
    Rectangle playerRect = {player.position.x, player.position.y, player.width, player.height};
    player.onGround = false;

    // Move X
    player.position.x += player.velocity.x * dt;
    playerRect.x = player.position.x;

    for (int i = 0; i < platformCount; i++) {
        if (CheckCollisionRecs(playerRect, platforms[i].rect)) {
            if (player.velocity.x > 0) {
                player.position.x = platforms[i].rect.x - player.width;
            } else if (player.velocity.x < 0) {
                player.position.x = platforms[i].rect.x + platforms[i].rect.width;
            }
            player.velocity.x = 0;
            playerRect.x = player.position.x;
        }
    }

    // Move Y
    player.position.y += player.velocity.y * dt;
    playerRect.y = player.position.y;

    for (int i = 0; i < platformCount; i++) {
        if (CheckCollisionRecs(playerRect, platforms[i].rect)) {
            if (player.velocity.y > 0) {
                player.position.y = platforms[i].rect.y - player.height;
                player.onGround = true;
            } else if (player.velocity.y < 0) {
                player.position.y = platforms[i].rect.y + platforms[i].rect.height;
            }
            player.velocity.y = 0;
            playerRect.y = player.position.y;
        }
    }
}