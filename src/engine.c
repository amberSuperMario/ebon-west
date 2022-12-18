#include <rogue.h>

void cursesSetup()
{
    initscr();
    noecho();
    curs_set(0);
}

void gameLoop()
{
    int ch;

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

        handleInput(ch);
        drawEverything();
    }
}

void closeGame()
{
    endwin();
    free(player);
}
