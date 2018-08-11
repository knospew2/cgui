#ifndef KEYS_H
#define KEYS_H
#include <stdbool.h>
#include <SDL2/SDL.h>

void initializeKeyboard(); 

bool keyDown(SDL_Scancode code); 

#endif
