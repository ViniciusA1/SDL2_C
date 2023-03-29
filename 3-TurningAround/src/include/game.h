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

struct Game {
        struct Player player;
        struct Window window;
};

// game structure
extern struct Game game;

// game.c

void initGame(int, int);
void gameLoop();
void endGame();

// events.c

bool verifyEvent(SDL_Event);
void keyboardEvent(SDL_Event);

// window.c

void updateWindow();

// player.c

void renderPlayer();
void setPlayerXY(short int);
void setLineXY();
