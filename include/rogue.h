#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h> // used for srand()
#include <math.h>
#include "vector.h"

// color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2

typedef struct
{
    int y;
    int x;
} Position;

typedef struct
{
    Position pos;
    int color;
    char ch;
    bool walkable;
    bool transparent;
    bool visible;
    bool seen;
    int toughness; // used for tunneling with a shovel, pickaxe, etc.
} Tile;

typedef struct
{
    int color;
    Position pos;
    char ch;
} Entity;



// draw.c
void drawMap();
void drawEntity(Entity*);
void drawEverything();

// fov.c
void makeFOV(Entity*);
void clearFOV(Entity*);
int getDistance(Position, Position);
bool isInMap(int, int);
bool lineOfSight(Position, Position);
int getSign(int);

// engine.c
void cursesSetup();
void gameLoop();
void closeGame();

// player.c
Entity* createPlayer(Position);
void handleInput(int);
void movePlayer(Position);

// map.c
void createMapTiles();
void setupMap();
void refineMap(int);
void freeMap();
void map_floodFill(Position, Vector*);
void map_identifySegments();
Position map_getStartPos();
int map_mainSegmentIndex();


// externs
extern Entity* player;
// map
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Tile** map;
extern Tile** map_cpy; // used to modify the map during iteration
extern Vector map_segments;
extern Vector current_segment;

#endif
