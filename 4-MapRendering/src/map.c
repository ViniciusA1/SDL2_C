#include "include/game.h"

int verifyMap(int wid, int heig, int map[][wid], char *map_name)
{
        FILE *input = fopen(map_name, "rb");
        int rect_amount;

        if(!input) {
                fprintf(stderr, "The map ""%s"" doesn't exist!\nCreating a new one!\n", map_name);
                return createNewMap(wid, heig, map, map_name);
        }

        fread(&rect_amount, sizeof(int), 1, input);
        fread(map, sizeof(*map) * heig, 1, input);

        fclose(input);
        return rect_amount;
}

int createNewMap(int wid, int heig, int map[][wid], char *filename)
{
        FILE *map_file = fopen(filename, "wb");
        int rect_amount = 2 * wid + 2 * (heig - 2);

        for(int i = 0; i < wid; i++) {
                map[0][i] = 1;
                map[heig-1][i] = 1;
        }

        for(int i = 1, j; i < heig-1; i++) {
                map[i][0] = 1;

                for(j = 1; j < wid-1; j++)
                        map[i][j] = 0;

                map[i][wid-1] = 1;
        }

        fwrite(&rect_amount, sizeof(int), 1, map_file);
        fwrite(map, sizeof(*map) * heig, 1, map_file);

        fclose(map_file);
        return rect_amount;
}


// Function receives the rectangles structure and the current map data.
// Creates and stores the XY position of every rectangle.
void createRects(SDL_Rect *rect, int map_wid, int map_heig, int current_map[][map_wid])
{
        int rect_id = 0;
        double rect_wid =  (double) game.window.WIDTH / map_wid;
        double rect_heig = (double) game.window.HEIGHT / map_heig;

        for(int i = 0, j; i < map_heig; i++) {
                for(j = 0; j < map_wid; j++) {
                        if(current_map[i][j]) {
                                rect[rect_id].x = j * (rect_wid + 2);
                                rect[rect_id].y = i * (rect_heig + 2);
                                rect[rect_id].w = rect_wid;
                                rect[rect_id].h = rect_heig;
                                rect_id++;
                        }
                }
        }
}

// Function receives the rectangle structure and the amount of objects.
// Render every map rectangle on the screen.
void renderRects(SDL_Rect *rects, int rect_amount)
{
        SDL_SetRenderDrawColor(game.window.render_ptr, 255, 255, 255, 255);
        SDL_RenderFillRects(game.window.render_ptr, rects, rect_amount);
        SDL_SetRenderDrawColor(game.window.render_ptr, 0, 0, 0, 255);
}
