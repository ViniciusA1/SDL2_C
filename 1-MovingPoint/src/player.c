#include "include/game.h"

void renderPlayer()
{
        SDL_SetRenderDrawColor(game.window.render_ptr, 255, 255, 255, 255);
        SDL_RenderDrawPoint(game.window.render_ptr, game.player.pos_x, game.player.pos_y);
        SDL_SetRenderDrawColor(game.window.render_ptr, 0, 0, 0, 255);
}

void moveXPosition(int amount)
{
        if(game.player.pos_x + amount > 0 && game.player.pos_x + amount < game.window.WIDTH)
                game.player.pos_x += amount;
}

void moveYPosition(int amount)
{
        if(game.player.pos_y + amount > 0 && game.player.pos_y + amount < game.window.HEIGHT)
                game.player.pos_y += amount;
}
