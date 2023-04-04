#include "include/game.h"
#include <SDL2/SDL_render.h>
#define STEP 0.25
#define FOG (SCREENWIDTH)
#define CORRECTION (SCREENWIDTH / 2.0) / tan(game->player.FOV / 2.0)

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
                double wallHeight, wallBegin, wallEnd;

                gotHit = false;
                while(!gotHit && wallDist < FOG) {
                        rayX = game->player.pos_x + (wallDist * cosRay);
                        rayY = game->player.pos_y + (wallDist * sinRay);
                        
                        if(checkColision(rayX, rayY, &game->scene))
                                gotHit = true;

                        wallDist += STEP;
                }

                if(wallDist > FOG) wallDist = 0;

                wallDist *= cos(rayAngle - game->player.angle);
                wallHeight = (game->scene.block_wid / wallDist) * CORRECTION;
                wallBegin = (SCREENHEIGHT - wallHeight) / 2;
                wallEnd = wallBegin + wallHeight;

                SDL_RenderDrawLine(game->window.render_ptr, i, wallBegin, i, wallEnd);
        }

        SDL_SetRenderDrawColor(game->window.render_ptr, 0, 0, 0, 255);
}
