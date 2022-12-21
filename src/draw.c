#include "rogue.h"

void drawMap()
{
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            if(map[y][x].visible)
            {
                mvaddch(y, x, map[y][x].ch | map[y][x].color);
            }
            else if(map[y][x].seen)
            {
                mvaddch(y, x, map[y][x].ch | COLOR_PAIR(SEEN_COLOR));
            }
            else
            {
                mvaddch(y, x, map[y][x].ch | map[y][x].color);
                //mvaddch(y, x, ' ');
            }
        }
    }
}

void drawEntity(Entity* entity)
{
    mvaddch(entity->pos.y, entity->pos.x, entity->ch | entity->color);
    /*
    if(map[entity->pos.y][entity->pos.x].visible)
    {
        mvaddch(entity->pos.y, entity->pos.x, entity->ch | entity->color);
    }
    else if(map[entity->pos.y][entity->pos.x].seen)
    {
        mvaddch(entity->pos.y, entity->pos.x, entity->ch | COLOR_PAIR(SEEN_COLOR));
    }
    else
    {
        mvaddch(entity->pos.y, entity->pos.x, ' ');
    }*/
}

void drawEverything()
{
    clear();
    drawMap();
    drawEntity(player);
}
