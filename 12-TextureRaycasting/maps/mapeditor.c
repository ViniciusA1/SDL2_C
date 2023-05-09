#include <SDL2/SDL_mouse.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <stdbool.h>
#define WIDTH 700
#define HEIGHT 700
#define MAPSTORAGE "mapstorage"
#define TEXTPATH "../textures/"
#define TEXTSTORAGE "texturestorage"
#define NAMELENGTH 11

struct Map {
        int maxSize;
        double blockSize;
};

typedef struct Window{
        SDL_Window *windowPtr;
        SDL_Renderer *renderPtr;
        SDL_Texture **textureBuffer;
        unsigned text_amnt;
        struct Map map;
} Win_t;


void mainMenu();
void showAvailableMaps();
void verifyUserInput(int);
void createMap();
void editMap(char *);
void initWindow(Win_t *);
void loadTextures(Win_t *);
void screenLoop(Win_t *, Uint8 (*)[]);
bool verifyEventType(Win_t *, SDL_Event, Uint8 (*)[], int);
void verifyMouseState(Win_t *, Uint8 (*)[], Uint32, int, int);
void verifyKeyboardEvent(Win_t *, SDL_KeyboardEvent, Uint8 (*)[], int);
void renderGrid(Win_t *);
void renderMatrix(Win_t *, Uint8 (*)[]);
void updateFrameBuffer(Win_t *);
void closeWindow(Win_t *);
void destroyTexture(Win_t *);
void removeMap(char (*)[], int, int);
void editOrRemove(char (*)[], int, int);
void saveMap(char *, int, Uint8 (*)[]);


int main()
{
        SDL_Init(SDL_INIT_VIDEO);
        FILE *mapStorage = fopen(MAPSTORAGE, "r");

        if(!mapStorage) {
                puts("There is no map filename! Creating one...");
                mapStorage = fopen(MAPSTORAGE, "w");
        }

        fclose(mapStorage);
        mainMenu();

        SDL_Quit();
}

void mainMenu()
{
        int userOpt;

        do 
        {
                printf("\e[1;1H\e[2J");
                puts("====|Menu|====");
                fputs("0) Leave\n"
                      "1) Create new map\n"
                      "2) Show available maps\n"
                      "> ", stdout);
                if(!scanf("%d", &userOpt)) continue;

                verifyUserInput(userOpt);
        } while(userOpt);
}

void verifyUserInput(int option)
{
        switch(option) {
                case 0: 
                        return;
                case 1: 
                        createMap();
                        break;
                case 2:
                        showAvailableMaps();
                        break;
                default:
                        puts("Invalid input!");
        }
}

void createMap()
{
        Win_t window;
        char mapName[NAMELENGTH];

        fputs("Enter the max map size (N x N): ", stdout);
        if(!scanf("%d", &window.map.maxSize)) return;
        fputs("Enter the map name: ", stdout);
        scanf(" %s", mapName);

        Uint8 matrix[window.map.maxSize][window.map.maxSize];
        memset(matrix, 0, sizeof(matrix));

        initWindow(&window);
        screenLoop(&window, matrix);
        closeWindow(&window);

        saveMap(mapName, window.map.maxSize, matrix);
        
        FILE *storage = fopen(MAPSTORAGE, "a");
        fprintf(storage, "%s\n", mapName);
        fclose(storage);
}

void editMap(char *mapName)
{
        Win_t window;
        FILE *editfile;

        editfile = fopen(mapName, "rb");
        
        if(!editfile) {
                puts("This map doesn't exists!");
                return;
        }

        fread(&window.map.maxSize, sizeof(int), 1, editfile);
        Uint8 map[window.map.maxSize][window.map.maxSize];
        fread(map, sizeof(map), 1, editfile);
        fclose(editfile);

        initWindow(&window);
        screenLoop(&window, map);
        closeWindow(&window);
        saveMap(mapName, window.map.maxSize, map);
}

void initWindow(Win_t *window)
{
        IMG_Init(IMG_INIT_PNG);

        window->windowPtr = SDL_CreateWindow("Map Editor", 
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            WIDTH, HEIGHT, 0);
        window->renderPtr = SDL_CreateRenderer(window->windowPtr, -1, 
                                                SDL_RENDERER_PRESENTVSYNC);

        window->map.blockSize = (double) WIDTH / window->map.maxSize;
        
        loadTextures(window);
}

void loadTextures(Win_t *window)
{
        char filename[20];
        sprintf(filename, "%s%s", TEXTPATH, TEXTSTORAGE);
        FILE *texture_storage = fopen(filename, "r");
        
        fscanf(texture_storage, "%d", &window->text_amnt);
        window->textureBuffer = malloc(sizeof(SDL_Texture *) 
                                        * window->text_amnt);

        for(int i = 0; i < window->text_amnt; i++) {
                char pathfile[30] = "\0";
                fscanf(texture_storage, "%s", filename);
                sprintf(pathfile, "%s%s", TEXTPATH, filename);
                SDL_Surface *temp_surface = IMG_Load(pathfile);
                if(temp_surface == NULL) printf("Error while loading texture\n");
                window->textureBuffer[i] = SDL_CreateTextureFromSurface(
                                            window->renderPtr, temp_surface);
                
                SDL_FreeSurface(temp_surface);
        }

        fclose(texture_storage);
}

void screenLoop(Win_t *window, Uint8 matrix[][window->map.maxSize])
{
        SDL_Event event;
        bool isRunning = true;
        int cur_opt = 1;

        while(isRunning) {
                while(SDL_PollEvent(&event))
                        isRunning = verifyEventType(window, event, matrix, cur_opt);

                int mouseX, mouseY;
                Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
                verifyMouseState(window, matrix, mouseState, mouseX, mouseY);

                renderMatrix(window, matrix);
                renderGrid(window);
                updateFrameBuffer(window);
        }
}

bool verifyEventType(Win_t *window, SDL_Event event, Uint8 matrix[][window->map.maxSize], int cur_opt)
{
        switch(event.type) {
                case SDL_QUIT:
                        return false;
                case SDL_KEYDOWN:
                        verifyKeyboardEvent(window, event.key, matrix, cur_opt);
                default:;
        }


        return true;
}

void verifyMouseState(Win_t *window, Uint8 map[][window->map.maxSize], Uint32 mouseState, int x, int y)
{
        x /= window->map.blockSize;
        y /= window->map.blockSize;

        if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
                map[y][x] = 1;
        else if(mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
                map[y][x] = 0;
}

void verifyKeyboardEvent(Win_t *window, SDL_KeyboardEvent key_pressed, 
                         Uint8 map[][window->map.maxSize], int opt)
{
        switch(key_pressed.keysym.sym) {
                case SDLK_c:
                        memset(map, 0, sizeof(Uint8) * window->map.maxSize 
                               * window->map.maxSize);
                        break;
                default:;
        }
}

void renderGrid(Win_t *window)
{
        SDL_SetRenderDrawColor(window->renderPtr, 128, 128, 128, 255);

        for(int i = 0; i <= WIDTH; i += window->map.blockSize)
                SDL_RenderDrawLine(window->renderPtr, i, 0, i, HEIGHT);

        for(int i = 0; i <= HEIGHT; i += window->map.blockSize)
                SDL_RenderDrawLine(window->renderPtr, 0, i, WIDTH, i);

        SDL_SetRenderDrawColor(window->renderPtr, 0, 0, 0, 255);
}

void renderMatrix(Win_t *window, Uint8 matrix[][window->map.maxSize])
{
        SDL_Rect rect;

        for(int i = 0, j; i < window->map.maxSize; i++) {
                for(j = 0; j < window->map.maxSize; j++) {
                        if(!matrix[i][j])
                                continue;
                        
                        rect.x = j * window->map.blockSize;
                        rect.y = i * window->map.blockSize;
                        rect.w = window->map.blockSize;
                        rect.h = window->map.blockSize;

                        SDL_RenderCopy(window->renderPtr, 
                                       window->textureBuffer[matrix[i][j]-1], 
                                       NULL, &rect);
                }
        }

}

void updateFrameBuffer(Win_t *window)
{
        SDL_RenderPresent(window->renderPtr);
        SDL_RenderClear(window->renderPtr);
}

void closeWindow(Win_t *window)
{
        SDL_DestroyWindow(window->windowPtr);
        SDL_DestroyRenderer(window->renderPtr);
        destroyTexture(window);
        IMG_Quit();
}

void destroyTexture(Win_t *window)
{
        for(int i = 0; i < window->text_amnt; i++)
                SDL_DestroyTexture(window->textureBuffer[i]);
        
        free(window->textureBuffer);
}

void removeMap(char mapNames[][NAMELENGTH], int index, int map_amount)
{
        if(remove(mapNames[index])) {
                puts("Invalid input!");
                return;
        }

        FILE *storage = fopen(MAPSTORAGE, "w");

        for(int i = 0; i < map_amount; i++) {
                if(strcmp(mapNames[index], mapNames[i]))
                        fprintf(storage, "%s\n", mapNames[i]);
        }

        fclose(storage);
}

void saveMap(char *mapName, int mapLimit, Uint8 map[][mapLimit])
{
        FILE *mapFile = fopen(mapName, "wb");

        fwrite(&mapLimit, sizeof(int), 1, mapFile);
        fwrite(map, sizeof(Uint8) * mapLimit * mapLimit, 1, mapFile);

        fclose(mapFile);
}

void showAvailableMaps()
{
        FILE *storage = fopen(MAPSTORAGE, "r");
        int userOpt, i;
        char mapLevel[100][NAMELENGTH];

        printf("\e[1;1H\e[2J");
        puts("====|Map List|====\n"
             "0) Leave");

        for(i = 1; fscanf(storage, "%s", mapLevel[i-1]) != EOF; i++)              
                printf("%d) %s\n", i, mapLevel[i-1]);

        fclose(storage);
        
        fputs("> ", stdout);
        if(!scanf("%d", &userOpt) || userOpt == 0 || 
                  userOpt < 0 || userOpt >= i) return;

        editOrRemove(mapLevel, userOpt - 1, i - 1);
}

void editOrRemove(char mapLevels[][NAMELENGTH], int index, int map_amnt)
{
        int userOpt;

        do {
                printf("\e[1;1H\e[2J");
                printf("====|Map name: %s|====\n"
                       "0) Leave\n"
                       "1) Edit\n"
                       "2) Remove\n",
                       mapLevels[index]);
                fputs("> ", stdout);

                if(!scanf("%d", &userOpt)) continue;
        } while(userOpt < 0 || userOpt > 2);

        switch(userOpt) {
                case 0: return;
                case 1: editMap(mapLevels[index]); break;
                case 2: removeMap(mapLevels, index, map_amnt);
        }
}
