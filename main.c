#include "main.h"


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
uint32_t RMASK = 0xff000000;
uint32_t GMASK = 0x00ff0000;
uint32_t BMASK = 0x0000ff00;
uint32_t AMASK = 0x000000ff;
#else
uint32_t RMASK = 0x000000ff;
uint32_t GMASK = 0x0000ff00;
uint32_t BMASK = 0x00ff0000;
uint32_t AMASK = 0xff000000;
#endif


Sprite *BOUND_SPRITE;
int main() {
    SDL_Window *window;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    initializeKeyboard();
    window = SDL_CreateWindow(
            "A SDL Window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_OPENGL
    );
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
    }
    SpriteList *sprites = newSpriteList();
    Sprite *sprite = newSpriteWithImage(10, 10, renderer, "assets/sample.bmp");
    BOUND_SPRITE = sprite;
    sprites = appendToSpriteList(sprites, sprite);
    int width;
    int height;
    SDL_GetWindowSize(window, &width, &height);
    SDL_Surface *backgroundSurface = SDL_CreateRGBSurface(0, 1, 1, 32, RMASK, GMASK, BMASK, AMASK);
    SDL_FillRect(backgroundSurface, NULL, 0xffffffff);
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    Environment *environment = makeNewEnvironment(sprites, backgroundTexture, width, height); 
    render(renderer, sprite);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    bool quit = false;
    while (!quit){
        msleep(10);
        if (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_MOUSEBUTTONDOWN: handleMouseDown(environment, &e); 
                case SDL_QUIT: quit = true; break;
                default: break;
            }
        }
        if (keyDown(SDL_SCANCODE_W)) {
            BOUND_SPRITE->dy = -1;
        } else if (keyDown(SDL_SCANCODE_S)) {
            BOUND_SPRITE->dy = 1;
        } else {
            BOUND_SPRITE->dy = 0;
        }

        if (keyDown(SDL_SCANCODE_A)) {
            BOUND_SPRITE->dx = -1;
        } else if (keyDown(SDL_SCANCODE_D)) {
            BOUND_SPRITE->dx = 1;
        } else {
            BOUND_SPRITE->dx = 0;
        }
        if (keyDown(SDL_SCANCODE_Q)) {
            BOUND_SPRITE->dTheta = -1;
        } else if (keyDown(SDL_SCANCODE_E)) {
            BOUND_SPRITE->dTheta = 1;
        } else {
            BOUND_SPRITE->dTheta = 0;
        }
        animate(window, renderer, sprites, backgroundTexture);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}

