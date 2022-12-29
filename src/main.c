#include "rogue.h"

const int MAP_HEIGHT = 25;
const int MAP_WIDTH = 100;

Entity* player;

int main() {
    engine_cursesSetup();

    map_createTiles();
    map_setup();
    map_refine(20);

    map_identifyRooms();

    Position startPos = map_getStartPos();
	MonsterType startType = Slinger;
    player = createPlayer(startPos, startType);
	player->name = "Azalea";

    engine_gameLoop();

    engine_closeGame();

    return 0;
}
