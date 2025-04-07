#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "globals.h"
#include "player.h"

extern int level[MAP_HEIGHT][MAP_WIDTH];

void DrawLevel();
void CheckPlayerCollision(Player &player);

#endif
