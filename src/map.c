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
            map[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
            map[y][x].walkable = false;
            map[y][x].transparent = false;
            map[y][x].visible = false;
            map[y][x].seen = false;

            map_cpy[y][x].ch = '#';
            map_cpy[y][x].walkable = false;
            map_cpy[y][x].transparent = false;
            map_cpy[y][x].visible = false;
            map_cpy[y][x].seen = false;
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
            // 50% of the time, carve out a floor
            int num = 1 + rand() % 100;
            if(num <= 50)
            {
                map[y][x].ch = '.';
                map[y][x].walkable = true;
                map[y][x].transparent = true;
                map[y][x].visible = false;
                map[y][x].seen = false;

                map_cpy[y][x].ch = '.';
                map_cpy[y][x].walkable = true;
                map_cpy[y][x].transparent = true;
                map_cpy[y][x].visible = false;
                map_cpy[y][x].seen = false;
            }
        }
    }
}

Position map_getStartPos()
{
    bool found = false;
    while(!found)
    {
        int randY = rand() % MAP_HEIGHT;
        int randX = rand() % MAP_WIDTH;
        Position randPos = { randY, randX };
        if(map[randY][randX].ch == '.') 
        {
            found = true;
            return randPos;
        }
    }
}

// Re-implement this whenever you feel like trying flood fill again.
/*)void map_flood_fill(Position pos)
{
    vector_init(&segments);

    Vector segment;
    vector_init(&segment);

    Vector toFill;
    vector_init(&toFill);
    vector_add(&toFill, &pos);

    while(vector_count(&toFill) > 0)
    {
        Position* posToCheck;  
        printf("- toFill count pre: %d -", vector_count(&toFill));
        posToCheck = (Position*)vector_get(&toFill, 0);
        vector_remove(&toFill, 0);
        if(!vector_contains(&segment, &posToCheck))
        {
            vector_add(&segment, &posToCheck); 

            Position north = { posToCheck->y - 1, posToCheck->x };
            Position south = { posToCheck->y + 1, posToCheck->x };
            Position east = { posToCheck->y, posToCheck->x + 1 };
            Position west = { posToCheck->y, posToCheck->x - 1 };

            map[posToCheck->y][posToCheck->x].ch = 'o';

            if(map_cpy[north.y][north.x].ch == '.')
            {
                if(!vector_contains(&toFill, &north))
                {
                    vector_add(&toFill, &north);
                }
            }
            if(map_cpy[south.y][south.x].ch == '.')
            {
                if(!vector_contains(&toFill, &south))
                {
                    vector_add(&toFill, &south);
                }
            }
            if(map_cpy[east.y][east.x].ch == '.')
            {
                if(!vector_contains(&toFill, &east))
                {
                    vector_add(&toFill, &east);
                }
            }
            if(map_cpy[west.y][west.x].ch == '.')
            {
                if(!vector_contains(&toFill, &west))
                {
                    vector_add(&toFill, &west);
                }
            }
        }
        printf("- toFill count post: %d -", vector_count(&toFill));
    }
    vector_add(&segments, &segment);
}*/

/*void map_get_segments()
{
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            if(map[y][x].ch == '.') 
            {
                Position pos = { y, x };
                map_flood_fill(pos);
            }
        }
    }
}*/

void refineMap(int cycles)
{
    // For any given tile...
    // If it has 3 or fewer adjacent walls, turn it into a floor
    // If it has 5 or more adjacent walls, turn it into a wall
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

                if(map[y][x].ch == '#')
                {
                    if(num <= 3)
                    {
                        map_cpy[y][x].ch = '.';
                        map_cpy[y][x].walkable = true;
                        map_cpy[y][x].transparent = true;
                    }
                }
                else if(map[y][x].ch == '.')
                {
                    if(num > 4)
                    {
                        map_cpy[y][x].ch = '#';
                        map_cpy[y][x].walkable = false;
                        map_cpy[y][x].transparent = false;
                    }
                }
            }
        }

        for(int y = 1; y < MAP_HEIGHT-1; y++)
        {
            for(int x = 1; x < MAP_WIDTH-1; x++) 
            {
                map[y][x].ch = map_cpy[y][x].ch;
                map[y][x].walkable = map_cpy[y][x].walkable;
                map[y][x].transparent = map_cpy[y][x].transparent;
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
