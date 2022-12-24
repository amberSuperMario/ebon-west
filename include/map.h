#ifndef MAP_H
#define MAP_H

#include "rogue.h"
#include "position.h"

void map_createTiles();
void map_setup();
void map_refine(int);
void map_free();
void map_floodFill(Position, Vector*);
void map_identifyRooms();
void map_removeDisconnectedRooms();
int map_mainRoomIndex();
Position map_getStartPos();

#endif
