#pragma once
#include "text.h"
#include "tile.h"
#include "window.h"
#include <stdbool.h>

#define SPEED_MOD 5.0
#define MIN_SPEED 50.0
#define MAX_SPEED 150.0
#define N_MENU_ITEMS 2
#define SNAKE_LENGTH (N_TILES * N_TILES)
#define SNAKE_SIZE ((size_t) (sizeof(struct Tile) * SNAKE_LENGTH))

enum Mode {
  MENU,
  GAME
};

enum Select {
  PLAY,
  EXIT
};

struct Tick {
  double target;
  double width;
};

struct State {
  enum Mode mode;
  enum Select select;
  int tail_index;
  struct Tick tick;
  struct Text current_score;
  struct Text speed;
  struct Text menu_items[N_MENU_ITEMS];
  struct Tile snake[SNAKE_LENGTH];
  // struct Text high_score;
};

struct State init_state();

struct Tick init_tick();

void move_tile(struct Direction dir, SDL_Rect *rect);

void reset_tiles(struct State *state);

void update_text_values(struct State *state);

void update_positions(struct State *state);

char *tick_to_str(struct Tick *tick);

bool loop(struct Window *window, struct State *state);
