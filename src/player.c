#include "rogue.h"

Entity* createPlayer(Position start_pos)
{
    Entity* newPlayer = calloc(1, sizeof(Entity));

    newPlayer->pos.y = start_pos.y;
    newPlayer->pos.x = start_pos.x;
    newPlayer->ch = '@';
    newPlayer->color = COLOR_PAIR(VISIBLE_COLOR);

    return newPlayer;
}

void handleInput(int input)
{
    Position newPos = { player->pos.y, player->pos.x };
    switch(input)
    {
        // Move up
        case 'w':
            newPos.y--;
            break;
        // Move down
        case 's':
            newPos.y++;
            break;
        // Move left
        case 'a':
            newPos.x--;
            break;
        // Move right
        case 'd':
            newPos.x++;
            break;
        default:
            break;
    }
    movePlayer(newPos);
}

void movePlayer(Position newPos)
{
    if(map[newPos.y][newPos.x].walkable)
    {
        clearFOV(player);
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
        makeFOV(player);
    }
}
