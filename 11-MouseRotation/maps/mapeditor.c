#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdbool.h>
#define WIDTH 700
#define HEIGHT 700
#define mapstorage "mapstorage"
#define NAMELENGTH 11

struct Buffer {
        int pos_i, pos_j;
        int type;
};

struct Map {
        int max_size;
        double block_size;
};

typedef struct Window{
        SDL_Window *window_ptr;
        SDL_Renderer *render_ptr;
        struct Map map;
} Win_t;


void mainMenu();
int getMapAmount();
int showAvailableMaps();
int getAvailableMaps(int *);
void verifyUserInput(int);
void createMap(int);
void editMap();
void initWindow(Win_t *);
void screenLoop(Win_t *, Uint8 (*)[]);
bool verifyEventType(Win_t *, SDL_Event, Uint8 (*)[], int);
void verifyMouseEvent(Win_t *, SDL_MouseButtonEvent, Uint8 (*)[], int);
void verifyKeyboardEvent(Win_t *, SDL_KeyboardEvent, Uint8 (*)[], int);
void renderGrid(Win_t *);
void renderMatrix(Win_t *, Uint8 (*)[]);
void updateRender(Win_t *);
void closeWindow(Win_t *);
void removeMap(int);
void saveMap(char *, int, Uint8 (*)[]);


int main()
{
        SDL_Init(SDL_INIT_VIDEO);
        FILE *map_storage = fopen("mapstorage", "r");

        if(!map_storage) {
                puts("There is no map filename! Creating one...");
                map_storage = fopen("mapstorage", "w");
        }

        fclose(map_storage);
        mainMenu();

        SDL_Quit();
}

void mainMenu()
{
        int user_opt;

        do 
        {
                printf("\e[1;1H\e[2J");
                puts("====|Menu|====");
                fputs("0) Leave\n"
                      "1) Create new map\n"
                      "2) Edit map\n"
                      "3) Remove map\n"
                      "> ", stdout);
                scanf("%d", &user_opt);

                verifyUserInput(user_opt);
        } while(user_opt);
}

void verifyUserInput(int option)
{
        int map_amnt = getMapAmount();

        switch(option) {
                case 0: 
                        return;
                case 1: 
                        createMap(map_amnt);
                        break;
                case 2:
                        editMap();
                        break;
                case 3:
                        removeMap(map_amnt);
                        break;
                default:
                        puts("Invalid input!");
        }
}

void createMap(int map_amount)
{
        Win_t window;
        char mapname[NAMELENGTH];

        fputs("Enter the max map size (N x N): ", stdout);
        scanf("%d", &window.map.max_size);

        Uint8 matrix[window.map.max_size][window.map.max_size];
        memset(matrix, 0, sizeof(matrix));

        initWindow(&window);
        screenLoop(&window, matrix);
        closeWindow(&window);

        sprintf(mapname, "%d", map_amount + 1);
        saveMap(mapname, window.map.max_size, matrix);
        
        FILE *storage = fopen(mapstorage, "a");
        fprintf(storage, "%d ", map_amount + 1);
        fclose(storage);
}

void editMap()
{
        Win_t window;
        FILE *editfile;
        int opt;
        char mapname[NAMELENGTH];

        opt = showAvailableMaps();

        if(opt == 0) return;

        sprintf(mapname, "%d", opt);
        editfile = fopen(mapname, "rb");
        
        if(!editfile) {
                puts("This map doesn't exists!");
                return;
        }

        fread(&window.map.max_size, sizeof(int), 1, editfile);
        Uint8 map[window.map.max_size][window.map.max_size];
        fread(map, sizeof(map), 1, editfile);
        fclose(editfile);

        initWindow(&window);
        screenLoop(&window, map);
        closeWindow(&window);
        saveMap(mapname, window.map.max_size, map);
}

int getMapAmount()
{
        int amount = 0;
        FILE *storage = fopen(mapstorage, "r");

        while(fscanf(storage, "%d", &amount) != EOF);

        fclose(storage);
        return amount;
}

void initWindow(Win_t *window)
{
        window->window_ptr = SDL_CreateWindow("Map Editor", 
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            WIDTH, HEIGHT, 0);
        window->render_ptr = SDL_CreateRenderer(window->window_ptr, -1, SDL_RENDERER_PRESENTVSYNC);

        window->map.block_size = (double) WIDTH / window->map.max_size;
}

void screenLoop(Win_t *window, Uint8 matrix[][window->map.max_size])
{
        SDL_Event event;
        bool isRunning = true;
        int cur_opt = 1;

        while(isRunning) {
                while(SDL_PollEvent(&event))
                        isRunning = verifyEventType(window, event, matrix, cur_opt);

                renderMatrix(window, matrix);
                renderGrid(window);
                updateRender(window);
        }
}

bool verifyEventType(Win_t *window, SDL_Event event, Uint8 matrix[][window->map.max_size], int cur_opt)
{
        switch(event.type) {
                case SDL_QUIT:
                        return false;
                case SDL_MOUSEBUTTONDOWN:
                        verifyMouseEvent(window, event.button, matrix, cur_opt);
                        break;
                case SDL_KEYDOWN:
                        verifyKeyboardEvent(window, event.key, matrix, cur_opt);
                default:;
        }


        return true;
}

void verifyMouseEvent(Win_t *window, SDL_MouseButtonEvent button_pressed, 
                      Uint8 map[][window->map.max_size], int opt)
{
        int i = button_pressed.y / window->map.block_size;
        int j = button_pressed.x / window->map.block_size;

        switch(button_pressed.button) {
                case SDL_BUTTON_LEFT:
                        printf("x: %d y: %d\n", button_pressed.x, button_pressed.y);
                        printf("i: %d j: %d\n", i, j);
                        map[i][j] = opt;
                        break;
                case SDL_BUTTON_RIGHT:
                        map[i][j] = 0;
                        break;
                default:;
        }
}

void verifyKeyboardEvent(Win_t *window, SDL_KeyboardEvent key_pressed, 
                         Uint8 map[][window->map.max_size], int opt)
{
        switch(key_pressed.keysym.sym) {
                case SDLK_c:
                        memset(map, 0, sizeof(Uint8) * window->map.max_size 
                               * window->map.max_size);
                        break;
                default:;
        }
}

void renderGrid(Win_t *window)
{
        SDL_SetRenderDrawColor(window->render_ptr, 128, 128, 128, 255);

        for(int i = 0; i <= WIDTH; i += window->map.block_size)
                SDL_RenderDrawLine(window->render_ptr, i, 0, i, HEIGHT);

        for(int i = 0; i <= HEIGHT; i += window->map.block_size)
                SDL_RenderDrawLine(window->render_ptr, 0, i, WIDTH, i);

        SDL_SetRenderDrawColor(window->render_ptr, 0, 0, 0, 255);
}

void renderMatrix(Win_t *window, Uint8 matrix[][window->map.max_size])
{
        SDL_Rect rect;

        SDL_SetRenderDrawColor(window->render_ptr, 255, 0, 0, 255);

        for(int i = 0, j; i < window->map.max_size; i++) {
                for(j = 0; j < window->map.max_size; j++) {
                        if(matrix[i][j] == 1) {
                                rect.x = j * window->map.block_size;
                                rect.y = i * window->map.block_size;
                                rect.w = window->map.block_size;
                                rect.h = window->map.block_size;
                                SDL_RenderFillRect(window->render_ptr, &rect);
                        }
                }
        }

        SDL_SetRenderDrawColor(window->render_ptr, 0, 0, 0, 255);
}

void updateRender(Win_t *window)
{
        SDL_RenderPresent(window->render_ptr);
        SDL_RenderClear(window->render_ptr);
}

void closeWindow(Win_t *window)
{
        SDL_DestroyWindow(window->window_ptr);
        SDL_DestroyRenderer(window->render_ptr);
}

void removeMap(int map_amount)
{
        int mapnames[map_amount];
        int opt;
        char mapname[NAMELENGTH];

        opt = getAvailableMaps(mapnames);

        if(opt == 0) return;

        sprintf(mapname, "%d", opt);

        if(remove(mapname)) {
                puts("Invalid input!");
                return;
        }

        FILE *storage = fopen(mapstorage, "w");

        for(int i = 0; i < map_amount; i++) {
                if(mapnames[i] != opt)
                        fprintf(storage, "%d ", mapnames[i]);
        }

        fclose(storage);
}

void saveMap(char *mapname, int map_limit, Uint8 map[][map_limit])
{
        FILE *mapfile = fopen(mapname, "wb");

        fwrite(&map_limit, sizeof(int), 1, mapfile);
        fwrite(map, sizeof(Uint8) * map_limit * map_limit, 1, mapfile);

        fclose(mapfile);
}

int showAvailableMaps()
{
        FILE *storage = fopen(mapstorage, "r");
        int user_opt;
        int map_level;

        puts("0) Leave");

        for(int i = 1; fscanf(storage, "%d", &map_level) != EOF; i++)              
                printf("%d) Level %d\n", i, map_level);

        fputs("> ", stdout);
        scanf("%d", &user_opt);

        fclose(storage);
        return user_opt;
}

int getAvailableMaps(int *mapnames)
{
        FILE *storage = fopen(mapstorage, "r");
        int user_opt;

        puts("0) Leave");

        for(int i = 1; fscanf(storage, "%d", &mapnames[i-1]) != EOF; i++)
                printf("%d) Level %d\n", i, mapnames[i-1]);

        fputs("> ", stdout);
        scanf("%d", &user_opt);

        fclose(storage);
        return user_opt;
}
