#include "include/game.h"

// Function receives the current extern events 
// and applies alteration in-game.
bool verifyUserEvent(SDL_Event cur_event, Game *game)
{
        int relX, relY;

        switch(cur_event.type) {
                case SDL_MOUSEMOTION:
                        SDL_GetRelativeMouseState(&relX, &relY);
                        game->player.angle += relX * 
                        game->player.turn_speed * 
                        game->window.refresh_time;
                        break;
                case SDL_QUIT:
                        return false;
        }

        return true;
}

// Function receives keyboard states and apply in-game.
// (Can handle multiple key).
void verifyKeyboardState(const Uint8 *keyboard, Game *game)
{
        // WASD basic movement (still need a lot of improvement)

        if(keyboard[SDL_SCANCODE_W] && keyboard[SDL_SCANCODE_A])
                movePlayer(game, -45 * ONEDEGREE, -45 * ONEDEGREE, 1);
        else if(keyboard[SDL_SCANCODE_W] && keyboard[SDL_SCANCODE_D])
                movePlayer(game, 45 * ONEDEGREE, 45 * ONEDEGREE, 1);
        else if(keyboard[SDL_SCANCODE_S] && keyboard[SDL_SCANCODE_A])
                movePlayer(game, 45 * ONEDEGREE, 45 * ONEDEGREE, -1);
        else if(keyboard[SDL_SCANCODE_S] && keyboard[SDL_SCANCODE_D])
                movePlayer(game, -45 * ONEDEGREE, -45 * ONEDEGREE, -1);
        else if(keyboard[SDL_SCANCODE_W])
                movePlayer(game, 0, 0, 1);
        else if(keyboard[SDL_SCANCODE_A])
                movePlayer(game, 90 * ONEDEGREE, 90 * ONEDEGREE, -1);
        else if(keyboard[SDL_SCANCODE_S])
                movePlayer(game, 0, 0, -1);
        else if(keyboard[SDL_SCANCODE_D])
                movePlayer(game, 90 * ONEDEGREE, 90 * ONEDEGREE, 1);
}
