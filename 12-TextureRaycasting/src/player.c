#include "include/game.h"

// Function render the player model and the direction line on screen.
void renderPlayer(Window *window, Player *player) 
{
        SDL_SetRenderDrawColor(window->render_ptr, 0, 255, 0, 255);
        SDL_RenderFillRect(window->render_ptr, &player->hitbox);
        SDL_SetRenderDrawColor(window->render_ptr, 0, 0, 0, 255);
}

// Function receives the direction signal ("+": up, "-": down) and updates
// the player XY position on screen.
void movePlayer(Game *game, double dx, double dy, short int signal) 
{
        double prev_x = game->player.hitbox.x;
        double prev_y = game->player.hitbox.y;

        game->player.hitbox.x += signal * cos(game->player.angle + dx) *
                              game->player.walk_speed * 
                              game->window.refresh_time;

        game->player.hitbox.y += signal * sin(game->player.angle + dy) *
                              game->player.walk_speed * 
                              game->window.refresh_time;

        if (checkColision(game->player.hitbox.x, game->player.hitbox.y, 
                          &game->scene))
        {
                game->player.hitbox.x = prev_x;
                game->player.hitbox.y = prev_y;
        }

        game->player.shakeDirection = signal;
}

// Checks if the given x and y coordinates are on a map wall.
bool checkColision(double x, double y, Map *scene) 
{
        return (x < 0 || y < 0 || x >= SCREENWIDTH || y >= SCREENHEIGHT ||
                scene->map[(int)y / scene->block_size]
                          [(int)x / scene->block_size]);
}
