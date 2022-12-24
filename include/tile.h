#ifndef TILE_H
#define TILE_H

#include "position.h"

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

#endif
