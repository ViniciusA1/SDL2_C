#include "include/game.h"
#define STEP 0.1
#define FOG 100

// Render the rays to build the scenery.
void renderRays(Game *game)
{
        bool gotHit = false;

        SDL_SetRenderDrawColor(game->window.render_ptr, 255, 0, 0, 255);

        for(int i = 0; i < SCREENWIDTH; i++) {
                float rayAngle = (game->player.angle - game->player.FOV / 2.0) 
                       + ((float) i / (float) SCREENWIDTH) * game->player.FOV;
               
                double cosRay = cos(rayAngle);
                double sinRay = sin(rayAngle);
                double rayX, rayY;
                double wallDist = 0;

                gotHit = false;
                while(!gotHit && wallDist < FOG) {
                        rayX = game->player.pos_x + (wallDist * cosRay);
                        rayY = game->player.pos_y + (wallDist * sinRay);
                        
                        if(checkColision(rayX, rayY, &game->scene))
                                gotHit = true;

                        wallDist += STEP;
                }

                SDL_RenderDrawLine(game->window.render_ptr, 
                                   game->player.pos_x, 
                                   game->player.pos_y, 
                                   rayX, rayY);
        }

        SDL_SetRenderDrawColor(game->window.render_ptr, 0, 0, 0, 255);
}
