#include "env.h"

Environment *makeNewEnvironment(SpriteList *sprites, SDL_Texture *background, int width, int height) {
    Environment *ret = salloc(sizeof(Environment));
    ret->sprites = sprites;
    ret->width = width;
    ret->height = height;
    ret->background = background;
    return ret;
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
