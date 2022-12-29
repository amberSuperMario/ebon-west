#include "rogue.h"

Tile** map;
Tile** map_cpy;
Tile** map_toFill;
Vector map_rooms;

char* map_name;

void map_createTiles()
{
    map = calloc(MAP_HEIGHT, sizeof(Tile*));
    map_cpy = calloc(MAP_HEIGHT, sizeof(Tile*));
    map_toFill = calloc(MAP_HEIGHT, sizeof(Tile*));

    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        map[y] = calloc(MAP_WIDTH, sizeof(Tile));
        map_cpy[y] = calloc(MAP_WIDTH, sizeof(Tile));
        map_toFill[y] = calloc(MAP_WIDTH, sizeof(Tile));

        for(int x = 0; x < MAP_WIDTH; x++)
        {
            Position newPos = { y, x };
            map[y][x].pos = newPos;
            map[y][x].ch = '#';
            map[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
            map[y][x].walkable = false;
            map[y][x].transparent = false;
            map[y][x].visible = false;
            map[y][x].seen = false;

            map_cpy[y][x].pos = newPos;
            map_cpy[y][x].ch = '#';
            map_cpy[y][x].walkable = false;
            map_cpy[y][x].transparent = false;
            map_cpy[y][x].visible = false;
            map_cpy[y][x].seen = false;

            map_toFill[y][x].pos = newPos;
            map_toFill[y][x].ch = '#';
        }
    }
}

void map_setup()
{
    srand(time(0));
    for(int y = 2; y < MAP_HEIGHT-2; y++)
    {
        for(int x = 2; x < MAP_WIDTH-2; x++)
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

                map_toFill[y][x].ch = '.';
            }
        }
    }
}

int map_mainRoomIndex()
{
    int main_room_index = -1;
    int max_room_size = 0;

    for(int i = 0; i < vector_count(&map_rooms); i++)
    {
        Vector* room = (Vector*)vector_get(&map_rooms, i);
        int room_size = vector_count(room);
        if(room_size > max_room_size)
        {
            printf("/**FOUND NEW BIGGEST MAP ROOM: %d**/", room_size);
            max_room_size = room_size;
            main_room_index = i;
        }
    }

    printf("/**BIGGEST ROOM SEGMENT SIZE IS... %d**/", max_room_size);
    return main_room_index;
}

void map_removeDisconnectedRooms()
{
    int main_room_index = map_mainRoomIndex();
    int rooms_total = vector_count(&map_rooms);

    if(rooms_total > 0)
    {
        for(int i = 0; i < rooms_total; i++)
        {
            if(i != main_room_index)
            {
                Vector* room = (Vector*)vector_get(&map_rooms, i);
                for(int j = 0; j < vector_count(room); j++)
                {
                    Position* pos = (Position*)vector_get(room, j);
                    printf("/**ROOMPOS: %d, %d**/", pos->x, pos->y);
                    map[pos->y][pos->x].ch = '#';
                    map[pos->y][pos->x].walkable = false;
                    map[pos->y][pos->x].transparent = false;
                    map[pos->y][pos->x].visible = false;
                    map[pos->y][pos->x].seen = false;
                }
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

void map_floodFill(Position pos, Vector* room)
{
    if(map_toFill[pos.y][pos.x].ch != '.')
    {
        printf("/**map_toFill[%d][%d] IS NOT A GROUND TILE...**/", pos.y, pos.x);
        printf("/**map_toFill[%d][%d] IS: %c**/", pos.y, pos.x, map_toFill[pos.y][pos.x].ch);
        return;
    }

    map_toFill[pos.y][pos.x].ch = '#';
    Position* new_pos = malloc(sizeof(Position*));
    new_pos->y = pos.y;
    new_pos->x = pos.x;
    vector_add(room, new_pos);

    Position north = { pos.y-1, pos.x };
    Position south = { pos.y+1, pos.x };
    Position east = { pos.y, pos.x+1 };
    Position west = { pos.y, pos.x-1 };

    if(north.y > 0 && map_toFill[north.y][north.x].ch == '.')
    {
        map_floodFill(north, room);
    }
    if(south.y < MAP_HEIGHT - 1 && map_toFill[south.y][south.x].ch == '.')
    {
        map_floodFill(south, room);
    }
    if(east.x > 0 && map_toFill[east.y][east.x].ch == '.')
    {
        map_floodFill(east, room);
    }
    if(west.x < MAP_WIDTH - 1 && map_toFill[west.y][west.x].ch == '.')
    {
        map_floodFill(west, room);
    }
}

void map_identifyRooms()
{
    vector_init(&map_rooms);

    int ground_count = 0;
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            if(map_toFill[y][x].ch == '.')
            {
                Vector* room = malloc(sizeof(Vector*));
                vector_init(room);

                Position new_pos = { y, x };
                map_floodFill(new_pos, room);
                vector_add(&map_rooms, room);
                printf("/**NUMBER OF TILES IN ROOM: %d**/", vector_count(room));
                printf("/**NUMBER OF TILES @ 0: %d**/", vector_count(vector_get(&map_rooms, 0)));
            }
        }
    }
    printf("/**MAP_ROOMS COUNT: %d**/", vector_count(&map_rooms));
}

void map_refine(int cycles)
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

                map_toFill[y][x].ch = map_cpy[y][x].ch;
            }
        }

        curCycle++;
    }
}

void map_addMonsters(Room* room)
{

}

void map_free()
{
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        free(map[y]);
        free(map_cpy[y]);
        free(map_toFill[y]);
    }
    free(map);
    free(map_cpy);
    free(map_toFill);
}
