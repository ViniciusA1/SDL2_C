#include "include/game.h"

// Function receives the current extern keyboard event 
// and applies alteration in-game.
void verifyKeyboardState(const Uint8 *keystate, Game *game)
{
        if(keystate[SDL_SCANCODE_W]) 
                movePlayer(game,  1);
        
        if(keystate[SDL_SCANCODE_S]) 
                movePlayer(game, -1);
        
        if(keystate[SDL_SCANCODE_A]) 
                game->player.angle -= game->player.turn_speed *
                game->window.refresh_time;
        
        if(keystate[SDL_SCANCODE_D]) 
                game->player.angle += game->player.turn_speed *
                game->window.refresh_time;
}
