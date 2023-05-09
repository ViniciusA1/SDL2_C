#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#define ONEDEGREE M_PI / 180
#define SCREENWIDTH 600
#define SCREENHEIGHT 600

typedef struct {
        SDL_Window *window_ptr;
        SDL_Renderer *render_ptr;
        double refresh_time;
} Window;

typedef struct {
        SDL_Rect hitbox;
        double walk_speed;
        double turn_speed;
        double angle;
        double FOV;
        short int shakeDirection;
} Player;

typedef struct {
        Uint8 **map;
        int map_size;
        int block_size;
} Map;

typedef struct {
        Player player;
        Window window;
        Map scene;
} Game;


// game.c

static void initGame(Game *);
static void gameConfigs(Game *);
static void gameLoop(Game *);
static void endGame(Game *);

// events.c

bool verifyUserEvent(SDL_Event, Game *);
void verifyKeyboardState(const Uint8 *, Game *);

// window.c

void updateWindow(Window *);

// player.c

void renderPlayer(Window *, Player *);
void movePlayer(Game *, double, double, short int);
bool checkColision(double, double, Map *);

// map.c

int allocateMap(char *, Map *);
void renderMap(Window *, Map *);
void renderGrid(Window *, Map *);
void deallocateMap(Map *);

// rays.c

void renderRays(Game *);
static inline double findRayDistance(Game *, double, int *);
