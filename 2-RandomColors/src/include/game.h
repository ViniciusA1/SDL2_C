#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

struct Window {
        int WIDTH, HEIGHT;
        SDL_Window *window_ptr;
        SDL_Renderer *render_ptr;
};

struct Game {
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

// colors.c

void renderColor();
int randomColor(int);
