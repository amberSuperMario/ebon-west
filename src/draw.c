#include <rogue.h>

void drawMap()
{
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            mvaddch(y, x, map[y][x].ch);
        }
    }
}

void drawEntity(Entity* entity)
{
    mvaddch(entity->pos.y, entity->pos.x, entity->ch);
}

void drawEverything()
{
    clear();
    drawMap();
    drawEntity(player);
}
