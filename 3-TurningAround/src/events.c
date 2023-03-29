#include "include/game.h"

bool verifyEvent(SDL_Event current_event)
{
        if(current_event.type == SDL_QUIT)
                return false;

        if(current_event.type == SDL_KEYDOWN)
                keyboardEvent(current_event);

        return true;
}

void keyboardEvent(SDL_Event key_event)
{
        switch(key_event.key.keysym.sym) {
                case SDLK_w: 
                             setPlayerXY(1); 
                             setLineXY(); 
                             break;
                case SDLK_s: 
                             setPlayerXY(-1); 
                             setLineXY(); 
                             break;
                case SDLK_a: 
                             game.player.angle -= game.player.turn_speed; 
                             setLineXY();
                             break;
                case SDLK_d: 
                             game.player.angle += game.player.turn_speed; 
                             setLineXY();  
                             break;
                default:;
        }
}
