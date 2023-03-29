#include "include/game.h"
#include <SDL2/SDL_stdinc.h>

int allocateMap(char *filename)
{
        FILE *mapfile = fopen(filename, "rb");

        if(!mapfile) {
                fputs("ERROR! The current map doesn't exists!\n", stderr);
                return 1;
        }

        getMapSize(mapfile);

        game.scene.map = malloc(game.scene.line_amnt * sizeof(Uint8 *));

        for(int i = 0; i < game.scene.line_amnt; i++)
                game.scene.map[i] = malloc(game.scene.column_amnt * sizeof(Uint8));

        for(int i = 0, j; i < game.scene.line_amnt; i++) {
                for(j = 0; j < game.scene.column_amnt; j++)
                        fread(&game.scene.map[i][j], sizeof(Uint8), 1, mapfile);
        }

        game.scene.block_wid  = game.window.WIDTH / game.scene.column_amnt;
        game.scene.block_heig = game.window.HEIGHT / game.scene.line_amnt;

        fclose(mapfile);
        return 0;
}

void getMapSize(FILE *file_ptr)
{
        fread(&game.scene.column_amnt, sizeof(int), 1, file_ptr);
        fread(&game.scene.line_amnt, sizeof(int), 1, file_ptr);
}

void deallocateMap()
{
        for(int i = 0; i < game.scene.column_amnt; i++)
                free(game.scene.map[i]);

        free(game.scene.map);
}

// Function receives the rectangles structure and the current map data.
// Creates and stores the XY position of every rectangle.
void renderMap()
{
        SDL_Rect rect;

        SDL_SetRenderDrawColor(game.window.render_ptr, 255, 255, 255, 255);

        for(int i = 0, j; i < game.scene.line_amnt; i++) {
                for(j = 0; j < game.scene.column_amnt; j++) {
                        if(game.scene.map[i][j]) {
                                rect.x = j * (game.scene.block_wid);
                                rect.y = i * (game.scene.block_heig);
                                rect.w = game.scene.block_wid;
                                rect.h = game.scene.block_heig;
                                SDL_RenderFillRect(game.window.render_ptr, &rect);
                        }
                }
        }

        SDL_SetRenderDrawColor(game.window.render_ptr, 0, 0, 0, 255);
}

