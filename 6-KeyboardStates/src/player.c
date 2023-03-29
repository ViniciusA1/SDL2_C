#include "include/game.h"


// Function render the player model and the direction line on screen.
void renderPlayer(Window *window, Player *player)
{
        SDL_SetRenderDrawColor(window->render_ptr, 255, 255, 255, 255);
        SDL_RenderDrawPoint(window->render_ptr, player->pos_x, player->pos_y);
        SDL_RenderDrawLine(window->render_ptr, player->pos_x, player->pos_y, 
                           player->line_x, player->line_y);
        SDL_SetRenderDrawColor(window->render_ptr, 0, 0, 0, 255);
}

// Function receives the direction signal ("+": up, "-": down) and updates
// the player XY position on screen.
void movePlayer(Player *player, Map *scene, short int signal)
{
        double prev_x = player->pos_x;
        double prev_y = player->pos_y;

        player->pos_x += signal * cos(player->angle) * player->walk_speed;
        player->pos_y += signal * sin(player->angle) * player->walk_speed;
        
        if(checkPlayerColision(player, scene)) {
                player->pos_x = prev_x;
                player->pos_y = prev_y;
        } else {
                player->line_x += (player->pos_x - prev_x);
                player->line_y += (player->pos_y - prev_y);
        }
}

// Function updates the line direction on screen.
void rotatePlayer(Player *player, short int signal)
{
        player->angle += signal * player->turn_speed;
        player->line_x = player->pos_x + (player->line_wid * cos(player->angle));
        player->line_y = player->pos_y + (player->line_wid * sin(player->angle));
}

bool checkPlayerColision(Player *player, Map *scene)
{
        if(scene->map[(int) player->pos_y / scene->block_heig]
                     [(int) player->pos_x / scene->block_wid])
                return true;

        return false;
}
