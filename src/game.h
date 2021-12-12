#include "text.h"
#include "tile.h"
#include "window.h"
#include <stdbool.h>

#define SPEED_MOD 5.0
#define MIN_SPEED 50.0
#define MAX_SPEED 150.0

struct Tick {
  double target;
  double width;
};

struct State {
  struct Tile snake[SNAKE_LENGTH];
  struct Tick tick;
  struct Text current_score;
  // struct Text high_score;
  struct Text speed;
  int index;
};

struct State init_state();

void move_tile(struct Direction dir, SDL_Rect *rect);

bool loop(struct Window *window, struct State *state);
