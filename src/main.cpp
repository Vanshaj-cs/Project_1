#include "raylib.h"
#include "globals.h"
#include "player.h"
#include "level.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Neon Depths");
    SetTargetFPS(60);

    Player player;
    InitPlayer(player);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        UpdatePlayer(player, dt);
        CheckPlayerCollision(player);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawLevel();
        DrawPlayer(player);

        DrawText("NEON DEPTHS", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}