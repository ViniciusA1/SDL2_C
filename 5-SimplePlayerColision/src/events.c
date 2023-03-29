#include "include/game.h"

// Function receives the current player event and verify It's type.
bool verifyEvent(SDL_Event current_event)
{
        // Quitting event.
        if(current_event.type == SDL_QUIT)
                return false;

        // Event for "key pressed".
        if(current_event.type == SDL_KEYDOWN)
                keyboardEvent(current_event);

        return true;
}


// Function receives the current extern keyboard event 
// and applies alteration in-game.
void keyboardEvent(SDL_Event key_event)
{
        // Verify the key "symbol".
        switch(key_event.key.keysym.sym) {
                case SDLK_w:
                             movePlayer(1); 
                             break;
                case SDLK_s: 
                             movePlayer(-1); 
                             break;
                case SDLK_a: 
                             game.player.angle -= game.player.turn_speed; 
                             rotatePlayer();
                             break;
                case SDLK_d: 
                             game.player.angle += game.player.turn_speed; 
                             rotatePlayer();  
                             break;
                default:
                             puts("Unknown key!");
        }
}
