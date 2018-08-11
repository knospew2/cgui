#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "sprite.h"
#include "msleep.h"
struct Environment {
    SpriteList *sprites;
    int width;
    int height;
    SDL_Texture *background;
};

typedef struct Environment Environment;

void animate(SDL_Window *window, SDL_Renderer *renderer, SpriteList *sprites, SDL_Texture *background); 

Environment *makeNewEnvironment(SpriteList *sprites, SDL_Texture *background, int width, int height);
#endif
