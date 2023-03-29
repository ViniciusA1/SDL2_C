#include "include/game.h"


// Function render the player model and the direction line on screen.
void renderPlayer()
{
        SDL_SetRenderDrawColor(game.window.render_ptr, 255, 255, 255, 255);
        SDL_RenderDrawPoint(game.window.render_ptr, game.player.pos_x, game.player.pos_y);
        SDL_RenderDrawLine(game.window.render_ptr, game.player.pos_x, game.player.pos_y, 
                           game.player.line_x, game.player.line_y);
        SDL_SetRenderDrawColor(game.window.render_ptr, 0, 0, 0, 255);
}

// Function receives the direction signal ("+": up, "-": down) and updates
// the player XY position on screen.
void movePlayer(short int signal)
{
        double prev_x = game.player.pos_x;
        double prev_y = game.player.pos_y;

        game.player.pos_x += signal * cos(game.player.angle) * game.player.walk_speed;
        game.player.pos_y += signal * sin(game.player.angle) * game.player.walk_speed;
        
        if(checkPlayerColision()) {
                game.player.pos_x = prev_x;
                game.player.pos_y = prev_y;
        } else {
                game.player.line_x += (game.player.pos_x - prev_x);
                game.player.line_y += (game.player.pos_y - prev_y);
        }
}

// Function updates the line direction on screen.
void rotatePlayer()
{
        game.player.line_x = game.player.pos_x + (game.player.line_wid * cos(game.player.angle));
        game.player.line_y = game.player.pos_y + (game.player.line_wid * sin(game.player.angle));
}

bool checkPlayerColision()
{
        if(game.scene.map[(int) game.player.pos_y / game.scene.block_heig]
                         [(int) game.player.pos_x / game.scene.block_wid])
                return true;

        return false;
}
