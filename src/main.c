#include "rogue.h"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Entity* player;

int main() {
    cursesSetup();

    createMapTiles();
    setupMap();
    refineMap(20);

    map_identifySegments();

    //int id = map_mainSegmentIndex();

    Position startPos = map_getStartPos();
    player = createPlayer(startPos);

    gameLoop();

    closeGame();

    return 0;
}
