#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#define ONEDEGREE M_PI / 180

struct Window {
        int WIDTH, HEIGHT;
        SDL_Window *window_ptr;
        SDL_Renderer *render_ptr;
};

struct Player {
        double pos_x, pos_y;
        double line_x, line_y;
        double line_wid;
        double walk_speed;
        double turn_speed;
        double angle;
};

struct Map {
        Uint8 **map;
        int column_amnt, line_amnt;
        int block_wid, block_heig;
};

struct Game {
        struct Player player;
        struct Window window;
        struct Map scene;
};

// game structure

extern struct Game game;

// game.c

void initGame(int, int);
void gameConfigs(int, int);
void gameLoop();
void endGame();

// events.c

bool verifyEvent(SDL_Event);
void keyboardEvent(SDL_Event);

// window.c

void updateWindow();

// player.c

void renderPlayer();
void movePlayer(short int);
void rotatePlayer();
bool checkPlayerColision();

// map.c

int allocateMap(char *);
void getMapSize(FILE *);
void createRects(SDL_Rect *);
void renderMap();
void deallocateMap();
