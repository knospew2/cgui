#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
#include "salloc.h"

enum _spriteType {
    RECT_TYPE,
    IMAGE_TYPE
};
typedef enum _spriteType spriteType;

struct _Sprite {
    spriteType type; 
    int x;
    int y;
    int dx;
    int dy;
    double dTheta;
    int width;
    int height;
    SDL_Point center;
    double theta; 
    SDL_Texture *texture;
};
typedef struct _Sprite Sprite;

struct _SpriteList {
    Sprite *sprite;
    struct _SpriteList *rest;
};

typedef struct _SpriteList SpriteList;

Sprite *newSprite(int x, int y, int width, int height);

Sprite *newSpriteWithImage(int x, int y, SDL_Renderer *renderer, char *filename);

SpriteList *newSpriteList();

SpriteList *appendToSpriteList(SpriteList *list, Sprite *sprite);

int render(SDL_Renderer *renderer, Sprite *sprite);

#endif
