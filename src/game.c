#include "game.h"
#include "colours.h"
#include "events.h"
#include "utils.h"
#include <stdlib.h>

struct Direction rand_dir() {
  int head_dx = rand_range(-1, 1);
  int head_dy = (1 ^ abs(head_dx)) * ((rand_range(0, 1) * 2) - 1);
  struct Direction dir = {
    .x = head_dx,
    .y = head_dy,
  };

  return dir;
}

struct SDL_Rect rand_rect() {
  SDL_Rect rect = {
    .x = rand_range(0, N_TILES) * TILE_SIZE,
    .y = rand_range(0, N_TILES) * TILE_SIZE,
    .w = TILE_SIZE,
    .h = TILE_SIZE,
  };

  return rect;
}

struct State init_state() {
  struct Tile head = {
    .dir = rand_dir(),
    .rect = rand_rect(),
    .colour = WHITE,
  };

  struct Tick tick = {
    .width = 30.0,
    .total = 0.0,
    .step = 0.5,
  };

  struct State state = {
    .tail = calloc(TAIL_SIZE, sizeof(struct Tile)),
    .tick = tick,
    .head = head,
  };

  return state;
}

bool is_next_frame(struct Tick *tick) {
  if (tick->total >= tick->step * 1000) {
    tick->total = 0.0;

    return true;
  }

  return false;
}

double next_tick(struct Tick *tick) {
  tick->total += tick->width;

  return 1000 / tick->width;
}

bool is_boundary(int pos, int delta) {
  switch (delta) {
  case 1:
    return pos == WIN_EDGE;
  case -1:
    return pos == 0;
  }

  return false;
}

bool is_moveable(struct Direction dir, int x, int y) {
  return !is_boundary(x, dir.x) && !is_boundary(y, dir.y);
}

void move(struct Direction dir, SDL_Rect *rect) {
  if (is_moveable(dir, rect->x, rect->y)) {
    rect->x += dir.x * TILE_SIZE;
    rect->y += dir.y * TILE_SIZE;
  }
}

void paint(SDL_Renderer *renderer, struct Tile *head) {
  SDL_Color col = head->colour;

  SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
  SDL_RenderFillRect(renderer, &head->rect);
}

bool loop(struct Window *window, struct State *state) {
  SDL_Event event;

  if (is_next_frame(&state->tick)) {
    move(state->head.dir, &state->head.rect);
  }

  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return false;
    }

    handle_event(state, &event);
  }

  paint(window->renderer, &state->head);

  SDL_RenderPresent(window->renderer);

  SDL_SetRenderDrawColor(window->renderer, BLACK.r, BLACK.g, BLACK.b, 255);
  SDL_RenderClear(window->renderer);

  SDL_Delay(next_tick(&state->tick));

  return true;
}
