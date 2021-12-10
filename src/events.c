#include "events.h"
#include "game.h"
#include <stdbool.h>

void apply_dir(struct Tile *head, struct Direction dir) {
  if (dirs_equal(inverse_dir(head->dir), dir)) {
    return;
  }

  head->next_dir = dir;
}

void handle_key(struct Tile *head, SDL_Keycode key) {
  switch (key) {
  case SDLK_w:
    apply_dir(head, UP);
    break;
  case SDLK_s:
    apply_dir(head, DOWN);
    break;
  case SDLK_a:
    apply_dir(head, LEFT);
    break;
  case SDLK_d:
    apply_dir(head, RIGHT);
    break;
  }
}

void handle_event(struct Tile *head, SDL_Event *event) {
  switch (event->type) {
  case SDL_KEYUP:
    handle_key(head, event->key.keysym.sym);
    break;
  }
}
