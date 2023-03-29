#include "include/game.h"

void renderRays(Game *game)
{
        SDL_SetRenderDrawColor(game->window.render_ptr, 0, 255, 0, 255);

        for(int i = 0; i < SCREENWIDTH; i++) {
                float rayAngle = (game->player.angle - game->player.FOV / 2.0) 
                       + ((float) i / (float) SCREENWIDTH) * game->player.FOV;

                //printf("Angle: %.2f\n", rayAngle);

                SDL_RenderDrawLine(game->window.render_ptr, 
                                   game->player.pos_x, 
                                   game->player.pos_y, 
                                   game->player.pos_x + 
                                   (game->player.line_wid * cos(rayAngle)), 
                                   game->player.pos_y + 
                                   (game->player.line_wid * sin(rayAngle)));
        }

        SDL_SetRenderDrawColor(game->window.render_ptr, 0, 0, 0, 255);
}
