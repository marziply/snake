#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>

#define NONE (struct Direction) { 0, 0 }
#define UP (struct Direction) { 0, -1 }
#define DOWN (struct Direction) { 0, 1 }
#define LEFT (struct Direction) { -1, 0 }
#define RIGHT (struct Direction) { 1, 0 }

struct State;

struct Direction {
  int x;
  int y;
};

struct Tile {
  struct Direction dir;
  struct Direction next_dir;
  SDL_Rect rect;
  SDL_Color colour;
};

static struct Direction dirs[4] = {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

void render_tile(struct Tile *tile, SDL_Renderer *renderer);

SDL_Rect rand_rect(struct State *state);

struct Direction rand_dir();

struct Direction inverse_dir(struct Direction dir);

bool dirs_equal(struct Direction dir_a, struct Direction dir_b);

bool is_boundary(int pos, int delta);

bool is_moveable(struct Direction dir, int x, int y);
