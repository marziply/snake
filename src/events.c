#include "colours.h"
#include "events.h"
#include <stdbool.h>

void apply_dir(struct Tile *head, struct Direction dir) {
  // Provided the intended direction is not in the opposite direction of
  // travel, sets the new direction to dir
  if (!dirs_equal(inverse_dir(head->dir), dir)) {
    head->next_dir = dir;
  }
}

void select_menu_item(struct Text *menu_items, int curr_idx, int sel_idx) {
  // Simply sets the new colour for selected menu items with a loop around
  // when selecting the first/last element
  struct Text *current_select = &menu_items[curr_idx];
  struct Text *next_select = &menu_items[sel_idx];

  set_text_colour(current_select, WHITE);
  set_text_colour(next_select, RED);
}

int prev_menu_item(struct State *state) {
  int prev_index = state->select == 0
    ? N_MENU_ITEMS - 1
    : state->select - 1;

  select_menu_item(state->menu_items, state->select, prev_index);

  return prev_index;
}

int next_menu_item(struct State *state) {
  int next_index = state->select == N_MENU_ITEMS - 1
    ? 0
    : state->select + 1;

  select_menu_item(state->menu_items, state->select, next_index);

  return next_index;
}

void handle_menu_select(struct State *state) {
  switch (state->select) {
  case PLAY:
    state->mode = GAME;
    break;
  case EXIT:
    exit(0);
    break;
  }
}

void handle_game_key(struct State *state, SDL_Keycode key) {
  struct Tile *head = &state->snake[1];

  switch (key) {
  case SDLK_w:
  case SDLK_UP:
    apply_dir(head, UP);
    break;
  case SDLK_s:
  case SDLK_DOWN:
    apply_dir(head, DOWN);
    break;
  case SDLK_a:
  case SDLK_LEFT:
    apply_dir(head, LEFT);
    break;
  case SDLK_d:
  case SDLK_RIGHT:
    apply_dir(head, RIGHT);
    break;
  case SDLK_r:
    reset_tiles(state);
    break;
  case SDLK_p:
  case SDLK_SPACE:
  case SDLK_RETURN:
    state->mode = MENU;
    break;
  }
}

void handle_menu_key(struct State *state, SDL_Keycode key) {
  switch (key) {
  case SDLK_w:
  case SDLK_UP:
    state->select = prev_menu_item(state);
    break;
  case SDLK_s:
  case SDLK_DOWN:
    state->select = next_menu_item(state);
    break;
  case SDLK_p:
  case SDLK_SPACE:
  case SDLK_RETURN:
    handle_menu_select(state);
    break;
  }
}

void handle_key_up(struct State *state, SDL_Keycode key) {
  if (key == SDLK_q || key == SDLK_ESCAPE) {
    exit(0);
  }

  switch (state->mode) {
  case MENU:
    handle_menu_key(state, key);
    break;
  case GAME:
    handle_game_key(state, key);
    break;
  }
}

void handle_event(struct State *state, SDL_Event *event) {
  switch (event->type) {
  case SDL_KEYUP:
    handle_key_up(state, event->key.keysym.sym);
    break;
  }
}
