#include "tile.h"
#include "window.h"
#include <stdbool.h>

typedef struct Tile Snake[SNAKE_LENGTH];

struct Tick {
  double target;
  double width;
};

struct State {
  int index;
  struct Tick tick;
  Snake snake;
};

struct State init_state();

struct Direction rand_dir();

void move_tile(struct Direction dir, SDL_Rect *rect);

double next_tick(struct Tick *tick);

bool is_next_frame(struct Tick *tick);

bool loop(struct Window *window, struct State  *state);
