#include "include/game.h"

// Updates the window with the created content.
void updateWindow()
{
        // Show the current render
        SDL_RenderPresent(game.window.render_ptr);
        // Clear the current render.
        SDL_RenderClear(game.window.render_ptr);
}
