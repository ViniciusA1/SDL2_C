#include "include/game.h"
#define MAPWIDTH 10
#define MAPHEIGHT 10

// Main game structure (holds information and data about the game).

struct Game game;


// Main function (initialize and quit SDL).
int main (int argc, char *argv[])
{
        initGame(800, 600);
        gameLoop();
        endGame();
        return 0;
}

// Function receives the screen width and height.
// Initializes the main window and renderer.
void initGame(int wid, int heig)
{
        SDL_Init(SDL_INIT_VIDEO);
        game.window.window_ptr = SDL_CreateWindow("Application", SDL_WINDOWPOS_CENTERED, 
                                                   SDL_WINDOWPOS_CENTERED, wid, heig, 0);

        game.window.render_ptr = SDL_CreateRenderer(game.window.window_ptr, -1, 
                                                    SDL_RENDERER_ACCELERATED);

        if(!game.window.window_ptr || !game.window.render_ptr)
                fprintf(stderr, "ERROR! %s", SDL_GetError());

        gameConfigs(wid, heig);
}

// Function receives the screen width and height.
// Set the basic game configs for player and window.
void gameConfigs(int screen_width, int screen_height)
{
        // Set screen width and height.

        game.window.WIDTH = screen_width;
        game.window.HEIGHT = screen_height;

        // Set initial player position.

        game.player.pos_x = screen_width  / 2.0;
        game.player.pos_y = screen_height / 2.0;
        
        // Set player walk speed and rotation speed ("camera").

        game.player.walk_speed = 5;
        game.player.turn_speed = 5 * ONEDEGREE;

        // Set player initial angle and line width.
        
        game.player.angle = 0;
        game.player.line_wid = 50;

        // Set the line initial position.
        setLineXY();
}

// Function holds the main game loop which keeps running
// the game until the user wants to stop.
void gameLoop()
{
        SDL_Event game_event;
        bool running = true;
        int main_map[MAPHEIGHT][MAPWIDTH];
        int rect_amount;
        SDL_Rect *rects;

        rect_amount = verifyMap(MAPWIDTH, MAPHEIGHT, main_map, "maps/first");
        rects = malloc(rect_amount * sizeof(SDL_Rect));
        createRects(rects, MAPWIDTH, MAPHEIGHT, main_map);

        while(running) {
                SDL_WaitEvent(&game_event);
                running = verifyEvent(game_event);
                renderRects(rects, rect_amount);
                renderPlayer();
                updateWindow();
                printf("degree: %.2lfº | x: %.2lf | y: %.2lf\n", 
                        fmod((game.player.angle * 180) / M_PI, 360), 
                        game.player.pos_x, game.player.pos_y);
        }

        free(rects);
}

// Destroy the main window, renderer and quit SDL (free allocated memory).
void endGame()
{
        SDL_DestroyRenderer(game.window.render_ptr);
        SDL_DestroyWindow(game.window.window_ptr);
        SDL_Quit();
}
