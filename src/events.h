#include <SDL2/SDL.h>
#include "map.h"

#define MAX_TICK 30.0
#define TICK 1.0 / MAX_TICK

SDL_Event sdl_event;
SDL_Event key_event;
SDL_Event update_event;

void poll ();
