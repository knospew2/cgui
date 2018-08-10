#ifndef MAIN_H
#define MAIN_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "sprite.h"
#include "msleep.h"
#include <stdint.h>

void animate(SDL_Window *window, SDL_Renderer *renderer, SpriteList *sprites, SDL_Texture *background); 
void handleKeyPress(SDL_Event *e); 
void handleKeyUp(SDL_Event *e);
uint32_t RMASK, GMASK, BMASK, AMASK;

#endif
