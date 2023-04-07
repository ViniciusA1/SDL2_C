#include "include/game.h"
#define PATH "../maps/"

int allocateMap(char *mapnumber, Map *scene)
{
        char filename[10];
        sprintf(filename, "%s%s", PATH, mapnumber);
        FILE *mapfile = fopen(filename, "rb");

        if(!mapfile) {
                fputs("ERROR! The current map doesn't exists!\n", stderr);
                return 1;
        }

        fread(&scene->map_size, sizeof(int), 1, mapfile);
        scene->map = malloc(scene->map_size * sizeof(Uint8 *));

        for(int i = 0; i < scene->map_size; i++)
                scene->map[i] = malloc(scene->map_size * sizeof(Uint8));

        for(int i = 0, j; i < scene->map_size; i++) {
                for(j = 0; j < scene->map_size; j++)
                        fread(&scene->map[i][j], sizeof(Uint8), 1, mapfile);
        }

        scene->block_size  = SCREENWIDTH / scene->map_size;

        fclose(mapfile);
        return 0;
}

void deallocateMap(Map *scene)
{
        for(int i = 0; i < scene->map_size; i++)
                free(scene->map[i]);

        free(scene->map);
}

// Function receives the rectangles structure and the current map data.
// Creates and stores the XY position of every rectangle.
void renderMap(Window *window, Map *scene)
{
        SDL_Rect rect;

        SDL_SetRenderDrawColor(window->render_ptr, 255, 255, 255, 255);

        for(int i = 0, j; i < scene->map_size; i++) {
                for(j = 0; j < scene->map_size; j++) {
                        if(scene->map[i][j]) {
                                rect.x = j * (scene->block_size);
                                rect.y = i * (scene->block_size);
                                rect.w = scene->block_size;
                                rect.h = scene->block_size;
                                SDL_RenderFillRect(window->render_ptr, &rect);
                        }
                }
        }

        SDL_SetRenderDrawColor(window->render_ptr, 0, 0, 0, 255);
}

void renderGrid(Window *window, Map *map)
{
        SDL_SetRenderDrawColor(window->render_ptr, 128, 128, 128, 255);

        for(int i = 0; i <= SCREENWIDTH; i += map->block_size)
                SDL_RenderDrawLine(window->render_ptr, i, 0, i, SCREENHEIGHT);

        for(int i = 0; i <= SCREENHEIGHT; i += map->block_size)
                SDL_RenderDrawLine(window->render_ptr, 0, i, SCREENWIDTH, i);

        SDL_SetRenderDrawColor(window->render_ptr, 0, 0, 0, 255);
}
