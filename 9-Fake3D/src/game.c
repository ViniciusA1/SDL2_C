#include "include/game.h"
#include <SDL2/SDL_render.h>

// Main function (initialize and quit SDL).
int main (int argc, char *argv[])
{
        Game game;
        
        initGame(&game);
        gameLoop(&game);
        endGame(&game);
        
        return 0;
}

// Function receives the screen width and height.
// Initializes the main window and renderer.
void initGame(Game *game)
{
        SDL_Init(SDL_INIT_VIDEO);
        game->window.window_ptr = SDL_CreateWindow("Application", 
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                        SCREENWIDTH, SCREENHEIGHT, 0);

        game->window.render_ptr = SDL_CreateRenderer(game->window.window_ptr, -1, 
                                                    SDL_RENDERER_ACCELERATED);
       
        SDL_RenderSetLogicalSize(game->window.render_ptr, SCREENWIDTH, SCREENHEIGHT);
        
        if(!game->window.window_ptr || !game->window.render_ptr)
                fprintf(stderr, "ERROR! %s", SDL_GetError());

        gameConfigs(game);
}

// Function receives the screen width and height.
// Set the basic game configs for player and window.
void gameConfigs(Game *game)
{
        // Set initial player position.

        game->player.pos_x = SCREENWIDTH  / 2.0;
        game->player.pos_y = SCREENHEIGHT / 2.0;
        
        // Set player walk, rotation speed and FOV.

        game->player.walk_speed = 30;
        game->player.turn_speed = (90 * ONEDEGREE);
        game->player.FOV = 60 * ONEDEGREE;

        //Set player initial angle and line width.
        
        game->player.angle = 0;
        game->player.line_wid = 200;
}

// Function holds the main game loop which keeps running
// the game until the user wants to stop.
void gameLoop(Game *game)
{
        SDL_Event game_event;
        bool running = true;
        Uint64 prev_time = 0, newest_time;

        if(allocateMap("1", &game->scene))
                return;

        while(running) {

                while(SDL_PollEvent(&game_event)) {
                        if(game_event.type == SDL_QUIT)
                                running = false;
                }

                newest_time = SDL_GetTicks64();
                game->window.refresh_time = (newest_time - prev_time) / 1000.0;
                prev_time = newest_time;

                if(game->window.refresh_time > 0)
                        printf("FPS: %lf\n", 1 / game->window.refresh_time);

                const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);
                verifyKeyboardState(keyboardstate, game);
                
                renderRays(game);
                updateWindow(&game->window);
        }

        deallocateMap(&game->scene);
}

// Destroy the main window, renderer and quit SDL (free allocated memory).
void endGame(Game *game)
{
        SDL_DestroyRenderer(game->window.render_ptr);
        SDL_DestroyWindow(game->window.window_ptr);
        SDL_Quit();
}
