#include "events.h"
#include "game.h"
#include <stdbool.h>

void apply_dir(struct State *state, struct Direction dir) {
  struct Tile *head = &state->snake[1];

  head->next_dir = dir;
}

void handle_key(struct State *state, SDL_Keycode key) {
  switch (key) {
  case SDLK_w:
    apply_dir(state, UP);
    break;
  case SDLK_s:
    apply_dir(state, DOWN);
    break;
  case SDLK_a:
    apply_dir(state, LEFT);
    break;
  case SDLK_d:
    apply_dir(state, RIGHT);
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
