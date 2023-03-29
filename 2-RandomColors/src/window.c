#include "include/game.h"

// Updates the window with created content.
void updateWindow()
{
        // Clear previous render.
        SDL_RenderPresent(game.window.render_ptr);
        SDL_RenderClear(game.window.render_ptr);
}
