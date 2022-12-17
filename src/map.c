#include <rogue.h>

Tile** map;
Tile** map_cpy;

void createMapTiles()
{
    map = calloc(MAP_HEIGHT, sizeof(Tile*));
    map_cpy = calloc(MAP_HEIGHT, sizeof(Tile*));

    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        map[y] = calloc(MAP_WIDTH, sizeof(Tile));
        map_cpy[y] = calloc(MAP_WIDTH, sizeof(Tile));

        for(int x = 0; x < MAP_WIDTH; x++)
        {
            map[y][x].ch = '#';
            map[y][x].walkable = false;
            map_cpy[y][x].ch = '#';
            map_cpy[y][x].walkable = false;
        }
    }
}

void setupMap()
{
    srand(time(0));
    for(int y = 1; y < MAP_HEIGHT-1; y++)
    {
        for(int x = 1; x < MAP_WIDTH-1; x++)
        {
            // 45% of the time, carve out a floor
            int num = 1 + rand() % 100;
            if(num <= 45)
            {
                map[y][x].ch = '.';
                map[y][x].walkable = true;
                map_cpy[y][x].ch = '.';
                map_cpy[y][x].walkable = true;

            }
        }
    }
}

void refineMap(int cycles)
{
    // For any given tile...
    // If it has 3 or fewer adjacent walls, turn it into a floor
    // If it has more than 5 adjacent walls, turn it into a wall
    // Otherwise, leave as is
    int curCycle = 1;
    while(curCycle <= cycles)
    {
        for(int y = 1; y < MAP_HEIGHT-1; y++)
        {
            for(int x = 1; x < MAP_WIDTH-1; x++) 
            {
                int num = 0;

                // Top-left
                if(map[y-1][x-1].ch == '#') num++;
                // Top-center
                if(map[y-1][x].ch == '#') num++;
                // Top-right
                if(map[y-1][x+1].ch == '#') num++;
                // Center-left
                if(map[y][x-1].ch == '#') num++;
                // Center-right
                if(map[y][x+1].ch == '#') num++;
                // Bottom-left
                if(map[y+1][x-1].ch == '#') num++;
                // Bottom-center
                if(map[y+1][x].ch == '#') num++;
                // Bottom-right
                if(map[y+1][x+1].ch == '#') num++;

                if(num <= 3)
                {
                    map_cpy[y][x].ch = '.';
                    map_cpy[y][x].walkable = true;
                }
                else if(num > 5)
                {
                    map_cpy[y][x].ch = '#';
                    map_cpy[y][x].walkable = false;
                }
            }
        }

        for(int y = 1; y < MAP_HEIGHT-1; y++)
        {
            for(int x = 1; x < MAP_WIDTH-1; x++) 
            {
                map[y][x].ch = map_cpy[y][x].ch;
                map[y][x].walkable = map_cpy[y][x].walkable;
            }
        }

        curCycle++;
    }
}

void freeMap()
{
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        free(map[y]);
        free(map_cpy[y]);
    }
    free(map);
    free(map_cpy);
}
