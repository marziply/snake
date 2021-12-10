#include "colours.h"
#include "events.h"
#include "game.h"
#include "utils.h"
#include <stdlib.h>

struct Direction rand_dir() {
  int head_dx = rand_range(-1, 1);
  int head_dy = (1 ^ abs(head_dx)) * ((rand_range(0, 1) * 2) - 1);

  struct Direction dir = {
    .x = head_dx,
    .y = head_dy
  };

  return dir;
}

struct SDL_Rect rand_rect() {
  SDL_Rect rect = {
    .x = rand_range(0, N_TILES) * TILE_SIZE,
    .y = rand_range(0, N_TILES) * TILE_SIZE,
    .w = TILE_SIZE,
    .h = TILE_SIZE
  };

  return rect;
}

struct State init_state(Snake *snake) {
  struct Tile head = {
    .dir = rand_dir(),
    .rect = rand_rect(),
    .colour = WHITE
  };

  struct Tile food = {
    .dir = (struct Direction) {
      .x = 0,
      .y = 0
    },
    .rect = rand_rect(),
    .colour = RED
  };

  struct Tick tick = {
    .target = 0.0,
    .width = 250.0
  };

  struct State state = {
    .tail_index = 0,
    .snake = snake,
    .tick = tick,
    .head = head,
    .food = food
  };

  *snake[state.tail_index++] = food;
  *snake[state.tail_index++] = head;

  return state;
}

bool is_next_frame(struct Tick *tick) {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), tick->target)) {
    tick->target = SDL_GetTicks() + tick->width;

    return true;
  }

  return false;
}

bool is_boundary(int pos, int delta) {
  return delta ? pos == ((delta + 1) / 2) * WIN_EDGE : false;
}

bool is_moveable(struct Direction dir, int x, int y) {
  return !is_boundary(x, dir.x) && !is_boundary(y, dir.y);
}

bool positions_equal(SDL_Rect *rect_a, SDL_Rect *rect_b) {
  return rect_a->x == rect_b->x && rect_a->y == rect_b->y;
}

void move(struct Direction dir, SDL_Rect *rect) {
  if (is_moveable(dir, rect->x, rect->y)) {
    rect->x += dir.x * TILE_SIZE;
    rect->y += dir.y * TILE_SIZE;
  }
}

void paint(SDL_Renderer *renderer, Snake *snake, int length) {
  for (int i = 0; i < length; i++) {
    struct Tile *tile = snake[i];
    SDL_Color col = tile->colour;

    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(renderer, &tile->rect);
  }
}

bool loop(struct Window *window, struct State *state) {
  SDL_Event event;

  if (is_next_frame(&state->tick)) {
    move(state->head.dir, &state->head.rect);

    if (positions_equal(&state->head.rect, &state->food.rect)) {
      state->food.rect = rand_rect();
    }
  }

  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return false;
    }

    handle_event(state, &event);
  }

  paint(window->renderer, state->snake, state->tail_index);

  SDL_RenderPresent(window->renderer);

  SDL_SetRenderDrawColor(window->renderer, BLACK.r, BLACK.g, BLACK.b, 255);
  SDL_RenderClear(window->renderer);

  return true;
}
