#include "rogue.h"

Entity* createPlayer(Position start_pos, MonsterType type)
{
    Entity* newPlayer = calloc(1, sizeof(Entity));

    newPlayer->pos.y = start_pos.y;
    newPlayer->pos.x = start_pos.x;
    newPlayer->ch = '@';
    newPlayer->color = COLOR_PAIR(VISIBLE_COLOR);

	newPlayer->type = type;
	switch(type)
	{
		case Slinger:
			newPlayer->strength = 8.0;
			newPlayer->agility = 15.0;
			newPlayer->intelligence = 7.0;
			break;
		case Breaker:
			newPlayer->strength = 16;
			newPlayer->agility = 10;
			newPlayer->intelligence = 4;
			break;
		case Mancer:
			newPlayer->strength = 8;
			newPlayer->agility = 7;
			newPlayer->intelligence = 15;
			break;
		case Brusher:
			newPlayer->strength = 12;
			newPlayer->agility = 12;
			newPlayer->intelligence = 6;
			break;
		case Watcher:
			newPlayer->strength = 5;
			newPlayer->agility = 10;
			newPlayer->intelligence = 15;
			break;
		default:
			newPlayer->strength = 10;
			newPlayer->agility = 10;
			newPlayer->intelligence = 10;
			break;
	}

    return newPlayer;
}

void calculateStats(Entity* player)
{
	player->health = 2 * player->strength;
	player->h_regen = 0.1 * player->strength;
	player->mana = 1.2 * player->intelligence;
	player->m_regen = 0.5 * player->intelligence;
	player->attack = 1 * player->strength; // fists by default!
	player->speed = 1;
	player->defense = 0.167 * player->agility;
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
        fov_clear(player);
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
        fov_make(player);
    }
}
