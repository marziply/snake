#include "events.h"
#include "game.h"
#include <stdbool.h>

void handle_key(struct State *state, SDL_Keycode key) {
  switch (key) {
  case SDLK_w:
    state->head.dir.x = 0;
    state->head.dir.y = -1;
    break;
  case SDLK_s:
    state->head.dir.x = 0;
    state->head.dir.y = 1;
    break;
  case SDLK_a:
    state->head.dir.x = -1;
    state->head.dir.y = 0;
    break;
  case SDLK_d:
    state->head.dir.x = 1;
    state->head.dir.y = 0;
    break;
  }
}

void handle_event(struct State *state, SDL_Event *event) {
  switch (event->type) {
  case SDL_KEYUP:
    handle_key(state, event->key.keysym.sym);
    break;
  }
}
