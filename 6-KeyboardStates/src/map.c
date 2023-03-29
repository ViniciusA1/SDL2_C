#include "include/game.h"

int allocateMap(char *filename, Map *scene)
{
        FILE *mapfile = fopen(filename, "rb");

        if(!mapfile) {
                fputs("ERROR! The current map doesn't exists!\n", stderr);
                return 1;
        }

        getMapSize(mapfile, &scene->column_amnt, &scene->line_amnt);

        scene->map = malloc(scene->line_amnt * sizeof(Uint8 *));

        for(int i = 0; i < scene->line_amnt; i++)
                scene->map[i] = malloc(scene->column_amnt * sizeof(Uint8));

        for(int i = 0, j; i < scene->line_amnt; i++) {
                for(j = 0; j < scene->column_amnt; j++)
                        fread(&scene->map[i][j], sizeof(Uint8), 1, mapfile);
        }

        scene->block_wid  = SCREENWIDTH / scene->column_amnt;
        scene->block_heig = SCREENHEIGHT / scene->line_amnt;

        fclose(mapfile);
        return 0;
}

void getMapSize(FILE *file_ptr, int *column_amount, int *line_amount)
{
        fread(column_amount, sizeof(int), 1, file_ptr);
        fread(line_amount, sizeof(int), 1, file_ptr);
}

void deallocateMap(Map *scene)
{
        for(int i = 0; i < scene->column_amnt; i++)
                free(scene->map[i]);

        free(scene->map);
}

// Function receives the rectangles structure and the current map data.
// Creates and stores the XY position of every rectangle.
void renderMap(Window *window, Map *scene)
{
        SDL_Rect rect;

        SDL_SetRenderDrawColor(window->render_ptr, 255, 255, 255, 255);

        for(int i = 0, j; i < scene->line_amnt; i++) {
                for(j = 0; j < scene->column_amnt; j++) {
                        if(scene->map[i][j]) {
                                rect.x = j * (scene->block_wid);
                                rect.y = i * (scene->block_heig);
                                rect.w = scene->block_wid;
                                rect.h = scene->block_heig;
                                SDL_RenderFillRect(window->render_ptr, &rect);
                        }
                }
        }

        SDL_SetRenderDrawColor(window->render_ptr, 0, 0, 0, 255);
}

