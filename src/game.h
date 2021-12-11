#include "tile.h"
#include "window.h"
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

struct Tick {
  double target;
  double width;
};

struct Score {
  char value[12];
  TTF_Font *font;
  SDL_Surface *surface;
  SDL_Rect rect;
};

struct State {
  struct Tile snake[SNAKE_LENGTH];
  struct Tick tick;
  struct Score score;
  int index;
};

struct State init_state();

void move_tile(struct Direction dir, SDL_Rect *rect);

double next_tick(struct Tick *tick);

bool is_next_frame(struct Tick *tick);

bool loop(struct Window *window, struct State *state);
