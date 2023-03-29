#include "include/game.h"


// Function render the player model and the direction line on screen.
void renderPlayer(Window *window, Player *player)
{
        SDL_SetRenderDrawColor(window->render_ptr, 255, 0, 0, 255);
        SDL_RenderDrawPoint(window->render_ptr, player->pos_x, player->pos_y);
        SDL_SetRenderDrawColor(window->render_ptr, 0, 0, 0, 255);
}

// Function receives the direction signal ("+": up, "-": down) and updates
// the player XY position on screen.
void movePlayer(Game *game, short int signal)
{
        double prev_x = game->player.pos_x;
        double prev_y = game->player.pos_y;

        game->player.pos_x += signal * cos(game->player.angle) * 
        (game->player.walk_speed * game->window.refresh_time);

        game->player.pos_y += signal * sin(game->player.angle) * 
        (game->player.walk_speed * game->window.refresh_time);
        
        if(checkPlayerColision(&game->player, &game->scene)) {
                game->player.pos_x = prev_x;
                game->player.pos_y = prev_y;
        }
}

bool checkPlayerColision(Player *player, Map *scene)
{
        if(scene->map[(int) player->pos_y / scene->block_heig]
                     [(int) player->pos_x / scene->block_wid])
                return true;

        return false;
}
