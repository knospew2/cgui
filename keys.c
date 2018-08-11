#include "keys.h"
#include <inttypes.h>

bool initialized = false;
const uint8_t *KEYBOARD; 
void initializeKeyboard() {
    KEYBOARD = SDL_GetKeyboardState(NULL);
    initialized = true;
}


bool keyDown(SDL_Scancode code) {
    if (!initialized) {
        printf("Contract violation! Keyboard manager uninitialized.\n");
        exit(1);
    }
    return KEYBOARD[code]; 
}


