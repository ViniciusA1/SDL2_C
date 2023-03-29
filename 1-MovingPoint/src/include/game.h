#include <SDL2/SDL.h>
#include <stdbool.h>

struct Window {
        int WIDTH, HEIGHT;
        SDL_Window *window_ptr;
        SDL_Renderer *render_ptr;
};

struct Player {
        int pos_x, pos_y;
        int velocity;
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
void moveXPosition(int);
void moveYPosition(int);
