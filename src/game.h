#include "tile.h"
#include "window.h"
#include <stdbool.h>

typedef struct Tile Snake[SNAKE_LENGTH];

struct Tick {
  double target;
  double width;
};

struct State {
  int tail_index;
  struct Tick tick;
  struct Tile head;
  struct Tile food;
  Snake *snake;
};

struct State init_state();

struct Direction rand_dir();

bool is_next_frame(struct Tick *tick);

double next_tick(struct Tick *tick);

bool loop(struct Window *window, struct State  *state);
