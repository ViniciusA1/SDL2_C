#include "include/game.h"

// Updates the window with the created content.
void updateWindow(Window *window)
{
        // Show the current render
        SDL_RenderPresent(window->render_ptr);
        // Clear the current render.
        SDL_RenderClear(window->render_ptr);
}
