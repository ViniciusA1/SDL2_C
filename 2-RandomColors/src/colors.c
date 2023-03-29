#include "include/game.h"

void renderColor()
{
        SDL_SetRenderDrawColor(game.window.render_ptr, randomColor(255), randomColor(255), randomColor(255), 255);
}

int randomColor(int limit)
{
        return rand() % limit;
}
