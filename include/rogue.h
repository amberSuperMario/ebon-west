#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h> // used for srand()
#include <math.h>
#include "entity.h"
#include "tile.h"
#include "vector.h"

// color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2

// externs
extern Entity* player;
// map
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Tile** map;
extern Tile** map_cpy; // used to modify the map during iteration
extern Vector map_rooms;

#endif
