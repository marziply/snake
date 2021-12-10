#include "colours.h"
#include "tile.h"
#include "utils.h"
#include "window.h"

struct Direction rand_dir() {
  return dirs[rand_range(0, 3)];
}

struct Direction inverse_dir(struct Direction dir) {
  return (struct Direction) {
    (~dir.x) + 1,
    (~dir.y) + 1
  };
}

struct SDL_Rect rand_rect() {
  return (SDL_Rect) {
    rand_range(0, N_TILES) * TILE_SIZE,
    rand_range(0, N_TILES) * TILE_SIZE,
    TILE_SIZE,
    TILE_SIZE
  };
}

// struct Tile create_tile();

bool dirs_equal(struct Direction dir_a, struct Direction dir_b) {
  return dir_a.x == dir_b.x && dir_a.y == dir_b.y;
}
