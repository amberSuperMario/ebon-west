#include <rogue.h>

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Entity* player;

int main() {
    Position start_pos = { 1, 1 };
    cursesSetup();

    createMapTiles();
    setupMap();
    player = createPlayer(start_pos);

    gameLoop();

    closeGame();

    return 0;
}
