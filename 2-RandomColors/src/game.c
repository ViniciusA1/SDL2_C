#include "include/game.h"
#include <SDL2/SDL_events.h>
#include <stdlib.h>

struct Game game;

int main (int argc, char *argv[])
{
        srand(time(NULL));
        initGame(800, 600);
        gameLoop();
        endGame();
        return 0;
}

void initGame(int wid, int heig)
{
        SDL_Init(SDL_INIT_VIDEO);
        game.window.window_ptr = SDL_CreateWindow("Application", SDL_WINDOWPOS_CENTERED, 
                                                   SDL_WINDOWPOS_CENTERED, wid, heig, 0);

        game.window.render_ptr = SDL_CreateRenderer(game.window.window_ptr, -1, 
                                                    SDL_RENDERER_ACCELERATED);

        if(!game.window.window_ptr || !game.window.render_ptr)
                printf("ERROR! %s", SDL_GetError());

        game.window.WIDTH = wid;
        game.window.HEIGHT = heig;
}

void gameLoop()
{
        SDL_Event game_event;
        bool running;

        while(running) {
                SDL_WaitEvent(&game_event);
                running = verifyEvent(game_event);
                updateWindow();
        }
}

void endGame()
{
        SDL_DestroyRenderer(game.window.render_ptr);
        SDL_DestroyWindow(game.window.window_ptr);
        SDL_Quit();
}
