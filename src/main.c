#include <rogue.h>

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Entity* player;

int main() {
    cursesSetup();

    createMapTiles();
    setupMap();
    refineMap(20);

    Position startPos = map_getStartPos();
    printf("X: %d, Y: %d", startPos.x, startPos.y);
    player = createPlayer(startPos);

    gameLoop();

    closeGame();

    return 0;
}
