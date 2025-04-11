#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "globals.h"
#include "player.h"

void InitLevel();

void UpdateLevel(Player &player);

void DrawLevel();

void CheckPlayerCollision(Player &player);

#endif
