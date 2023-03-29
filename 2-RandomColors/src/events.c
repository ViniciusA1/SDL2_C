#include "include/game.h"

bool verifyEvent(SDL_Event current_event)
{
        if(current_event.type == SDL_QUIT)
                return false;
        
        if(current_event.type == SDL_KEYDOWN && current_event.key.keysym.sym == SDLK_c)
                renderColor();

        return true;
}
