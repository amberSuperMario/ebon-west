#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h> // used for srand()

typedef struct
{
    int y;
    int x;
} Position;

typedef struct
{
    char ch;
    bool walkable;
} Tile;

typedef struct
{
    Position pos;
    char ch;
} Entity;

// draw.c
void drawMap();
void drawEntity(Entity* entity);
void drawEverything();

// engine.c
void cursesSetup();
void gameLoop();
void closeGame();

// player.c
Entity* createPlayer(Position start_pos);
void handleInput(int input);
void movePlayer(Position newPos);

// map.c
void createMapTiles();
void setupMap();
void refineMap(int cycles);
void freeMap();

// externs
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Entity* player;
extern Tile** map;
extern Tile** map_cpy; // used to modify the map during iteration

#endif
