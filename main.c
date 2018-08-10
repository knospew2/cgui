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
    render(renderer, sprite);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    bool quit = false;
    while (!quit){
        if (SDL_PollEvent(&e)){
            switch (e.type) {
                case SDL_QUIT: quit = true; break;
                case SDL_KEYDOWN: handleKeyPress(&e); break;
                case SDL_KEYUP: handleKeyUp(&e); break;
                case SDL_MOUSEBUTTONDOWN: quit = true; break;
                default: break;
            }
        }
        animate(window, renderer, sprites, backgroundTexture);
        msleep(10);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void animate(SDL_Window *window, SDL_Renderer *renderer, SpriteList *sprites, SDL_Texture *background) {
    SDL_RenderCopy(renderer, background, NULL, NULL); 
    while (sprites->rest != NULL) {
        Sprite *sprite = sprites->sprite;
        sprite->x += sprite->dx;
        sprite->y += sprite->dy;
        sprite->theta += sprite->dTheta;
        render(renderer, sprite);
        sprites = sprites->rest;
    }
    SDL_RenderPresent(renderer);
}
void handleKeyPress(SDL_Event *e) {
    switch (e->key.keysym.sym) {
        case SDLK_w: BOUND_SPRITE->dx = -1; BOUND_SPRITE->dy = 0; break;  
        case SDLK_a: BOUND_SPRITE->dx = 1; BOUND_SPRITE->dy = 0; break;
        case SDLK_s: BOUND_SPRITE->dy = -1; BOUND_SPRITE->dx = 0; break;
        case SDLK_d: BOUND_SPRITE->dy = 1; BOUND_SPRITE->dx = 0; break;
        case SDLK_e: BOUND_SPRITE->dTheta = 1; break;
        case SDLK_q: BOUND_SPRITE->dTheta = -1; break; 
        default: break;
    }
}
void handleKeyUp(SDL_Event *e) {
    BOUND_SPRITE->dy = 0;
    BOUND_SPRITE->dx = 0;
    BOUND_SPRITE->dTheta = 0;
}
