#include "rogue.h"

void cursesSetup()
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

void gameLoop()
{
    int ch;

    makeFOV(player);
    drawEverything();

    while(ch = getch())
    {
        if(ch == 'q')
        {
            break;
        }
        else if(ch == 'g')
        {
            // iterate on map
            refineMap(1);
        }
        else if(ch == 'r')
        {
            map_removeDisconnectedSegments();
        }

        handleInput(ch);
        drawEverything();
    }
}

void closeGame()
{
    endwin();
    free(player);
}
