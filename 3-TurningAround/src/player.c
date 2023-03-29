#include "include/game.h"

void renderPlayer()
{
        SDL_SetRenderDrawColor(game.window.render_ptr, 255, 255, 255, 255);
        SDL_RenderDrawPoint(game.window.render_ptr, game.player.pos_x, game.player.pos_y);
        SDL_RenderDrawLine(game.window.render_ptr, game.player.pos_x, game.player.pos_y, 
                           game.player.line_x, game.player.line_y);
        SDL_SetRenderDrawColor(game.window.render_ptr, 0, 0, 0, 255);
}

void setPlayerXY(short int signal)
{
        game.player.pos_x += signal * cos(game.player.angle) * game.player.walk_speed;
        game.player.pos_y += signal * sin(game.player.angle) * game.player.walk_speed;
}

void setLineXY()
{
        game.player.line_x = game.player.pos_x + game.player.line_wid * cos(game.player.angle);
        game.player.line_y = game.player.pos_y + game.player.line_wid * sin(game.player.angle);
}
