#include "include/game.h"
#include <SDL2/SDL_events.h>

bool verifyEvent(SDL_Event current_event)
{
        if(current_event.type == SDL_QUIT)
                return false;

        if(current_event.type == SDL_KEYDOWN)
                keyboardEvent(current_event);

        return true;
}

void keyboardEvent(SDL_Event key_event)
{
        switch(key_event.key.keysym.sym) {
                case SDLK_w: moveYPosition(-game.player.velocity); break;
                case SDLK_s: moveYPosition(game.player.velocity);  break;
                case SDLK_a: moveXPosition(-game.player.velocity); break;
                case SDLK_d: moveXPosition(game.player.velocity);  break;
                default:;
        }
}
