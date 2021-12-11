#include "colours.h"
#include "game.h"
#include "tile.h"
#include "utils.h"

bool tile_vacant(struct State *state, SDL_Rect rect) {
  tile_foreach(tile) {
    if (SDL_RectEquals(&rect, &tile->rect)) {
      return false;
    }
  }

  return true;
}

struct SDL_Rect rand_rect(struct State *state) {
  SDL_Rect *positions = calloc(SNAKE_LENGTH, sizeof(SDL_Rect));
  int free_index = 0;

  for (int x = 0; x < N_TILES; x++) {
    for (int y = 0; y < N_TILES; y++) {
      SDL_Rect rect = {
        (x * TILE_SIZE),
        (y * TILE_SIZE),
        TILE_SIZE,
        TILE_SIZE
      };

      if (tile_vacant(state, rect)) {
        positions[free_index++] = rect;
      }
    }
  }

  return positions[rand_range(0, SNAKE_LENGTH - state->index)];
}

struct Direction rand_dir() {
  return dirs[rand_range(0, 3)];
}

struct Direction inverse_dir(struct Direction dir) {
  return (struct Direction) {
    (~dir.x) + 1,
    (~dir.y) + 1
  };
}

bool dirs_equal(struct Direction dir_a, struct Direction dir_b) {
  return dir_a.x == dir_b.x && dir_a.y == dir_b.y;
}

bool is_boundary(int pos, int delta) {
  return delta ? pos == ((delta + 1) / 2) * WIN_EDGE : false;
}

bool is_moveable(struct Direction dir, int x, int y) {
  return !is_boundary(x, dir.x) && !is_boundary(y, dir.y);
}

void move_tile(struct Direction dir, SDL_Rect *rect) {
  if (is_moveable(dir, rect->x, rect->y)) {
    rect->x += dir.x * TILE_SIZE;
    rect->y += dir.y * TILE_SIZE;
  }
}
