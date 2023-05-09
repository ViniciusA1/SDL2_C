#include "include/game.h"
#define CORRECTION (SCREENWIDTH / (2 * tan(game->player.FOV / 2.0)))

// Render the rays to build the scenery.
void renderRays(Game *game) 
{
        for (int i = 0; i < SCREENWIDTH; i++) {
                double rayAngle = (game->player.angle - game->player.FOV / 2.0) +
                                  ((float)i / (float)SCREENWIDTH) * game->player.FOV;

                int color;
                double wallDist, wallHeight, wallBegin, wallEnd;

                wallDist = findRayDistance(game, rayAngle, &color) *
                            cos(rayAngle - game->player.angle);

                wallHeight = (game->scene.block_size / wallDist) * CORRECTION;
                wallBegin = (SCREENHEIGHT - wallHeight) / 2;
                wallEnd = wallBegin + wallHeight;

                SDL_SetRenderDrawColor(game->window.render_ptr, 255 / color, 0, 0, 255);
                SDL_RenderDrawLine(game->window.render_ptr, i, wallBegin, i, wallEnd);
        }

        SDL_SetRenderDrawColor(game->window.render_ptr, 0, 0, 0, 255);
}

static inline double findRayDistance(Game *game, double rayAngle, int *colorSide) 
{

        int mapX, mapY;
        int stepX, stepY;
        double dx, dy;
        double sideX, sideY;
        double cosRay = cos(rayAngle);
        double sinRay = sin(rayAngle);

        mapX = (int)game->player.hitbox.x;
        mapY = (int)game->player.hitbox.y;
        dx = (cosRay == 0 ? 1e30 : fabs(1 / cosRay));
        dy = (sinRay == 0 ? 1e30 : fabs(1 / sinRay));

        cosRay < 0 ? (stepX = -1, sideX = (game->player.hitbox.x - mapX) * dx)
                  : (stepX = 1, sideX = (mapX + 1.0 - game->player.hitbox.x) * dx);

        sinRay < 0 ? (stepY = -1, sideY = (game->player.hitbox.y - mapY) * dy)
                  : (stepY = 1, sideY = (mapY + 1.0 - game->player.hitbox.y) * dy);

        while (1) {
                if (sideX < sideY) {
                        sideX += dx;
                        mapX += stepX;
                        *colorSide = 1;
                } else {
                        sideY += dy;
                        mapY += stepY;
                        *colorSide = 2;
                }

                if (checkColision(mapX, mapY, &game->scene))
                        break;
        }

        return (*colorSide == 1 ? (sideX - dx) : (sideY - dy));
}
