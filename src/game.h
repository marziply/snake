#include "tile.h"
#include "window.h"
#include <stdbool.h>

typedef struct Tile Tail[N_TILES][N_TILES];

struct Tick {
  double target;
  double width;
};

struct State {
  struct Tick tick;
  struct Tile head;
  struct Tile food;
  Tail *tail;
};

struct State init_state();

struct Direction rand_dir();

bool is_next_frame(struct Tick *tick);

double next_tick(struct Tick *tick);

bool loop(struct Window *window, struct State  *state);
