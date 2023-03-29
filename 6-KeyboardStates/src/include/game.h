#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#define ONEDEGREE M_PI / 180
#define SCREENWIDTH 800
#define SCREENHEIGHT 600

typedef struct {
        SDL_Window *window_ptr;
        SDL_Renderer *render_ptr;
} Window;

typedef struct {
        double pos_x, pos_y;
        double line_x, line_y;
        double line_wid;
        double walk_speed;
        double turn_speed;
        double angle;
} Player;

typedef struct {
        Uint8 **map;
        int column_amnt, line_amnt;
        int block_wid, block_heig;
} Map;

typedef struct {
        Player player;
        Window window;
        Map scene;
} Game;


// game.c

void initGame(Game *);
void gameConfigs(Game *);
void gameLoop(Game *);
void endGame(Game *);

// events.c

void verifyKeyboardState(const Uint8 *, Game *);

// window.c

void updateWindow(Window *);

// player.c

void renderPlayer(Window *, Player *);
void movePlayer(Player *, Map *, short int);
void rotatePlayer(Player *, short int);
bool checkPlayerColision(Player *, Map *);

// map.c

int allocateMap(char *, Map *);
void getMapSize(FILE *, int *, int *);
void renderMap(Window *, Map *);
void deallocateMap(Map *);
