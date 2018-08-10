#include "sprite.h"

Sprite *newSprite(int x, int y, int width, int height) {
    Sprite *ret = salloc(sizeof(Sprite));
    ret->x = x;
    ret->y = y;
    ret->dx = 0;
    ret->dy = 0;
    ret->width = width;
    ret->height = height;
    ret->texture = NULL;
    ret->type = RECT_TYPE;
    ret->theta = 0;
    ret->center.x = x + width/2;
    ret->center.y = y + height/2;
    return ret;
}
Sprite *newSpriteWithImage(int x, int y, SDL_Renderer *renderer, char *filename) {
    Sprite *ret = newSprite(x, y, 0, 0);
    SDL_Surface *image = SDL_LoadBMP(filename);
    if (image == NULL) {
        printf("Unable to load asset %s", filename);
    }
    ret->width = image->w;
    ret->height = image->h;
    ret->texture = SDL_CreateTextureFromSurface(renderer, image);
    ret->type = IMAGE_TYPE;
    ret->center.x = x + image->w/2;
    ret->center.y = y + image->h/2;
    ret->dTheta = 0;
    return ret;
}

SpriteList *newSpriteList() {
    SpriteList *ret = salloc(sizeof(SpriteList));
    ret->rest = NULL;
    ret->sprite = NULL;
    return ret;
}

SpriteList *appendToSpriteList(SpriteList *list, Sprite *sprite) {
    SpriteList *new = newSpriteList();
    new->rest = list;
    new->sprite = sprite;
    return new;
}
int render(SDL_Renderer *renderer, Sprite *sprite) {
    if (sprite->type == IMAGE_TYPE) {
        //gotta be this one for now
        SDL_Rect startRect;
        startRect.x = 0;
        startRect.y = 0;
        startRect.w = sprite->width;
        startRect.h = sprite->height;
        SDL_Rect endRect;
        endRect.x = sprite->x;
        endRect.y = sprite->y;
        endRect.w = sprite->width;
        endRect.h = sprite->height;
        SDL_RenderCopyEx(renderer, sprite->texture, &startRect, &endRect, sprite->theta, &sprite->center, SDL_FLIP_NONE); 
        return 0;
    } else {
        printf("Error! Can't render rectangle.");
        return 1;
    }
}
/*int draw(SDL_Surface *surface, Sprite *sprite) {
    if (sprite->type == RECT_TYPE) {
        SDL_Rect rect;
        rect.x = sprite->x;
        rect.y = sprite->y;
        rect.w = sprite->width;
        rect.h = sprite->height;
        SDL_FillRect(surface, &rect, 0x00ff0000);
    } else if (sprite->type == IMAGE_TYPE) {
        SDL_Rect startRect;
        startRect.x = 0;
        startRect.y = 0;
        startRect.w = sprite->width;
        startRect.h = sprite->height;
        SDL_Rect endRect;
        endRect.x = sprite->x;
        endRect.y = sprite->y;
        endRect.w = sprite->width;
        endRect.h = sprite->height;
        int ret = SDL_BlitSurface(sprite->image, &startRect, surface, &endRect);
        if (ret != 0) {
            printf("Error: %s", SDL_GetError());
            return 1;
        }
    }
    return 0;
}*/
