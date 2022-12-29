#include "rogue.h"

Vector message_log;

void draw_border(int start_y, int start_x, int height, int width)
{
	int total_height = height+start_y;
	int total_width = width+start_x;
	for(int y = start_y; y < total_height; y++)
	{
		for(int x = start_x; x < total_width; x++)
		{
			// edges
			if(y == start_y && x < total_width-1)
			{
				mvaddch(y, x, ACS_HLINE);
			}
			else if(y == total_height-1 && x < total_width-1)
			{
				mvaddch(y, x, ACS_HLINE);
			}
			else if(y < total_height-1 && x == start_x)
			{
				mvaddch(y, x, ACS_VLINE);
			}
			else if(y < total_height-1 && x == total_width-1)
			{
				mvaddch(y, x, ACS_VLINE);
			}

			// Corners
			if(y == start_y && x == start_x)
			{
				mvaddch(y, x, ACS_ULCORNER);
			}
			else if(y == start_y && x == total_width-1)
			{
				mvaddch(y, x, ACS_URCORNER);
			}
			else if(y == total_height-1 && x == start_x)
			{
				mvaddch(y, x, ACS_LLCORNER);
			}
			else if(y == total_height-1 && x == total_width-1)
			{
				mvaddch(y, x, ACS_LRCORNER);
			}
		}
	}
}

void draw_map()
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
                //mvaddch(y, x, map[y][x].ch | map[y][x].color);
                mvaddch(y, x, ' ');
            }
        }
    }
}

void draw_entity(Entity* entity)
{
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
    }
}

void draw_text(int y, int x, char* message)
{
	mvprintw(y, x, message);
}

void draw_labels()
{
	// Name and class
	if(player == NULL)
	{
		mvprintw(1, MAP_WIDTH+1, "Noname the Vagabond");
	}
	else
	{
		char src[15];
		char* name1 = malloc(sizeof(char*));
		char* name2 = " the ";
		char* name3 = malloc(sizeof(char*));

		if(player->name == NULL)
			name1 = "Noname";
		else 
			name1 = player->name;

		if(player->type == Slinger)
			name3 = "Slinger";
		else
			name3 = "Vagabond";

		strcpy(src, name1);
		strcat(src, name2);
		strcat(src, name3);

		mvprintw(1, MAP_WIDTH+1, src);
	}
	// map name
	if(map_name == NULL)
	{
		mvprintw(2, MAP_WIDTH+1, "Unknown Area");
	}
	// Attributes
	mvprintw(4, MAP_WIDTH+1, "Strength:");
	mvprintw(5, MAP_WIDTH+1, "Agility:");
	mvprintw(6, MAP_WIDTH+1, "Intelligence:");
	mvprintw(7, MAP_WIDTH+1, "Alignment:");
	//mvprintw(8, MAP_WIDTH+1, "Storm Level:");
	mvprintw(9, MAP_WIDTH+1, "Money:");
	mvprintw(10, MAP_WIDTH+1, "Hit Points:");
	mvprintw(11, MAP_WIDTH+1, "Level:");
}

void draw_message_log(int from_pos)
{
	Position screen_pos = { x: 0, y: 0 };
	if(from_pos > vector_count(&message_log))
		return;

	for(int i = from_pos; i < vector_count(&message_log); i++)
	{
	;	
	}
}

void draw_all()
{
    clear();
    draw_map();
	// Map border
	draw_border(0, 0, MAP_HEIGHT, MAP_WIDTH);
	// Message border
	draw_border(MAP_HEIGHT, 0, 10, MAP_WIDTH);
	// Stats border
	draw_border(0, MAP_WIDTH, MAP_HEIGHT+10, 30);
	draw_labels();
    draw_entity(player);
}
