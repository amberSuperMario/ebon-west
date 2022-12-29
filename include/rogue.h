#define _XOPEN_SOURCE_EXTENDED

#ifndef ROGUE_H
#define ROGUE_H

#include <math.h>
#include <ncursesw/curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // used for srand()

// Vector limit
#define VECTOR_INITIAL_LIMIT 16

// Color pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2

// Character sets 
#define UNKNOWN		=	' '
#define EMPTY		=	'.'
#define WATER		=   '~'
#define WALL		=   '#'
#define ROCK		=   '*'
#define CACTUS		=	'$'
#define FIRE		=   '^'
#define PLAYER		=   '@'

// Enumerations
typedef enum MonsterType {
	Vagabond,
	Slinger,
	Breaker,
	Mancer,
	Brusher,
	Watcher,
	Bat,
	Spider,
	Creep
} MonsterType;

typedef enum WeaponType {
	Fist,
	Claw,
	Pistol
} WeaponType;

typedef enum WeaponAttribute {
	Strength,
	Agility,
	Intelligence
} WeaponAttribute;

// Structs
typedef struct Vector
{
    void** data;
    int limit;
    int count;
} Vector;

typedef struct 
{
    int y;
    int x;
} Position;

typedef struct 
{
    Position pos;
    int color;
    char ch;
    bool walkable;
    bool transparent;
    bool visible;
    bool seen;
    int toughness; // used for tunneling with a shovel, pickaxe, etc.
} Tile;

typedef struct 
{
    Tile* tiles;
    // Feature** features;
    // Monster** monsters;
    // Item** items;
    // Terrain** terrain;
} Room;

typedef struct Weapon {
	WeaponType type;
	int color;
	char ch;
	Position pos;
	WeaponAttribute attribute;
} Weapon;

typedef struct Entity
{
	// Player (and some monster) types:
	// - Slinger: uses pistols and guns with long range, specialize in agility
	// - Breaker: uses slow & strong melee weapons, specialize in strength
	// - Mancer: uses tomes to summon allies to do battle, specialize in intelligence
	// - Brusher: uses fast & quick weapons, specialize in strength & agility 
	// - Watcher: uses staves & spell scrolls, specialize in intelligence
	MonsterType type;
	char* name;
    int color;
	char ch;
	Position pos;
	int pathfinding;
	int isPlayer;

	// Attributes
	double strength;
	double agility;
	double intelligence;

	// Stats calculated based on attributes
	double health;		// 2 per pt of strength
	double h_regen;		// 0.1 per pt of strength
	double mana;		// 1.2 per pt of intelligence
	double m_regen;		// 0.5 per pt of intelligence
	double attack;		// dependent on weapon; 1 per pt of main attribute
	double speed;		// flat value independent of attributes
	double defense;		// 0.167 per pt of agility (only displays in whole increments)

	// equipment
	Vector* inventory;
	Weapon* rightHand;
	Weapon* leftHand;
} Entity;

// Draw methods
void draw_map();
void draw_entity(Entity*);
void draw_text(int, int, char*);
void draw_all();

// Engine methods
void engine_cursesSetup();
void engine_gameLoop();
void engine_closeGame();

// FOV methods
void fov_make(Entity*);
void fov_clear(Entity*);
int fov_getDistance(Position, Position);
bool fov_isInMap(int, int);
bool fov_lineOfSight(Position, Position);
int getSign(int);

// Map methods
void map_createTiles();
void map_setup();
void map_refine(int);
void map_free();
void map_floodFill(Position, Vector*);
void map_identifyRooms();
void map_removeDisconnectedRooms();
int map_mainRoomIndex();
Position map_getStartPos();
void map_addMonsters(Room*);

// Player methods
Entity* createPlayer(Position, MonsterType);
void handleInput(int);
void movePlayer(Position);

// Vector methods
void vector_init(Vector*);
void vector_add(Vector*, void*);
void vector_remove(Vector*, int);
void* vector_get(Vector*, int);
bool vector_contains(Vector*, void*);
int vector_count(Vector*);
void vector_free(Vector*);

// Extern 
extern Entity* player;
// map
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Tile** map;
extern Tile** map_cpy; // used to modify the map during iteration
extern Vector map_rooms;
extern char* map_name;
// etc.
extern Vector message_log;

#endif
