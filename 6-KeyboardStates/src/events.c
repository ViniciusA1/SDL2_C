#include "include/game.h"

// Function receives the current extern keyboard event 
// and applies alteration in-game.
void verifyKeyboardState(const Uint8 *keystate, Game *game)
{
        if(keystate[SDL_SCANCODE_W]) movePlayer(&game->player, &game->scene,  1);
        if(keystate[SDL_SCANCODE_S]) movePlayer(&game->player, &game->scene, -1);
        if(keystate[SDL_SCANCODE_A]) rotatePlayer(&game->player, -1);
        if(keystate[SDL_SCANCODE_D]) rotatePlayer(&game->player, 1);
}
