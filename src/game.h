#include "tile.h"
#include "window.h"

typedef struct Tile Tail[N_TILES][N_TILES];

struct Tick {
  double width;
  double total;
  double step;
};

struct State {
  struct Tick *tick;
  struct Tile *head;
  Tail *tail;
};

struct State init_state();

bool is_next_frame(struct Tick *tick);

double next_tick(struct Tick *tick);

bool loop(struct Window *window, struct State *state);
