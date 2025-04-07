#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

struct Player {
    Vector2 position;
    Vector2 velocity;
    float width;
    float height;
    bool onGround;
};

void InitPlayer(Player &player);
void UpdatePlayer(Player &player, float dt);
void DrawPlayer(const Player &player);

#endif