#include "rogue.h"

void engine_cursesSetup()
{
    initscr();
    noecho();
    curs_set(0);

    if(has_colors())
    {
        start_color();
        init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
    }
}

void engine_gameLoop()
{
    int ch;

    fov_make(player);
    draw_all();

    while(ch = getch())
    {
        if(ch == 'q')
        {
            break;
        }
        else if(ch == 'g')
        {
            // iterate on map
            map_refine(1);
        }
        else if(ch == 'r')
        {
            map_removeDisconnectedRooms();
        }

        handleInput(ch);
        draw_all();
    }
}

void engine_closeGame()
{
    endwin();
    free(player);
    map_free();
}
