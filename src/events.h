#include <SDL2/SDL.h>

struct Events {
  SDL_Event sdl_event;
  SDL_Event key_event;
  SDL_Event update_event;
};
