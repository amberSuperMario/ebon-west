#ifndef PLAYER_H
#define PLAYER_H

#include "rogue.h"
#include "entity.h"

Entity* createPlayer(Position);
void handleInput(int);
void movePlayer(Position);

#endif
