#include "colours.h"
#include "game.h"
#include "tile.h"
#include "utils.h"

void render_tile(struct Tile *tile, SDL_Renderer *renderer) {
  SDL_Color col = tile->colour;

  SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
  SDL_RenderFillRect(renderer, &tile->rect);
}

bool is_tile_vacant(struct State *state, SDL_Rect rect) {
  // Loops through all tiles to check if it is currently vacant of any snake
  // tiles by checking if their rect matches the current rect
  tile_foreach(v) {
    if (SDL_RectEquals(&rect, &v_tile->rect)) {
      return false;
    }
  }

  return true;
}

struct SDL_Rect rand_rect(struct State *state, int modifier) {
  SDL_Rect *positions = calloc(SNAKE_LENGTH, sizeof(SDL_Rect));
  int free_idx = 0;

  // Iterates over all possible tile values to generate a one dimensional
  // array so a tile can be selected randomly
  for (int x = modifier; x < N_TILES - modifier; x++) {
    for (int y = modifier; y < N_TILES - modifier; y++) {
      SDL_Rect rect = {
        (x * TILE_SIZE),
        (y * TILE_SIZE),
        TILE_SIZE,
        TILE_SIZE
      };

      // Append to the positions array only if that particular tile is
      // vacant
      if (is_tile_vacant(state, rect)) {
        positions[free_idx++] = rect;
      }
    }
  }

  return positions[rand_range(0, free_idx)];
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
  // Checks if pos is equal to one of either 0 or WIN_EDGE
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
