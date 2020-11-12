#include <SDL2/SDL.h>

#define MAX_TICK 30.0
#define TICK 1.0 / MAX_TICK

struct Map;
typedef struct Events {
  SDL_Event sdl_event;
  SDL_Event key_event;
  SDL_Event update_event;
} Events;

void poll(struct Map map);
