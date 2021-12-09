#include <SDL2/SDL.h>

struct State;
struct Events {
  SDL_Event sdl_event;
  SDL_Event key_event;
  SDL_Event update_event;
};

void handle_event(struct State *state, SDL_Event *event);
