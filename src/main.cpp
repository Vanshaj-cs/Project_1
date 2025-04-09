#include "raylib.h"
#include "globals.h"
#include "player.h"
#include "level.h"

Camera2D camera = { 0 };

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Neon Depths");
    SetTargetFPS(60);

    Player player;
    InitPlayer(player);

    camera.target = player.position;   // Center of camera
    camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        UpdatePlayer(player, dt);
        CheckPlayerCollision(player);

        camera.target = (Vector2){
            player.position.x + player.width / 2.0f,
            player.position.y + player.height / 2.0f
        };

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        DrawLevel();
        DrawPlayer(player);

        EndMode2D();

        DrawText("NEON DEPTHS", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}