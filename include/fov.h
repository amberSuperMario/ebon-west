#ifndef FOV_H
#define FOV_H

#include "rogue.h"
#include "position.h"
#include "entity.h"

void fov_make(Entity*);
void fov_clear(Entity*);
int fov_getDistance(Position, Position);
bool fov_isInMap(int, int);
bool fov_lineOfSight(Position, Position);
int getSign(int);

#endif
