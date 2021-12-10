#include "colours.h"
#include "events.h"
#include "game.h"
#include "utils.h"
#include <stdlib.h>

struct State init_state() {
  return (struct State) {
    2,
    {
      0.0,
      250.0
    },
    {
      {
        NONE,
        NONE,
        rand_rect(),
        RED
      },
      {
        rand_dir(),
        NONE,
        rand_rect(),
        WHITE
      }
    }
  };
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

void move_tile(struct Direction dir, SDL_Rect *rect) {
  if (is_moveable(dir, rect->x, rect->y)) {
    rect->x += dir.x * TILE_SIZE;
    rect->y += dir.y * TILE_SIZE;
  }
}

void update_positions(struct State *state) {
  for (int i = 0; i < state->index; i++) {
    struct Tile *tile = &state->snake[i];

    for (int j = 2; j < state->index; j++) {
      struct Tile *comp = &state->snake[j];

      if (i == j) {
        continue;
      }

      if (positions_equal(&tile->rect, &comp->rect)) {
        printf("Game over!\nPoints: %d\n", state->index - 2);

        exit(0);
      }
    }

    if (!dirs_equal(tile->next_dir, NONE)) {
      tile->dir = tile->next_dir;
      tile->next_dir = NONE;
    }

    if (i > 1) {
      struct Tile *prev = &state->snake[i - 1];

      tile->next_dir = prev->dir;
    }

    move_tile(tile->dir, &tile->rect);
  }
}

void eat_food(struct State *state, struct Tile *food) {
  struct Tile *prev = &state->snake[state->index - 1];
  struct Direction dir = inverse_dir(prev->dir);

  food->rect = rand_rect();
  state->tick.width -= SPEED_MOD;
  state->snake[state->index++] = (struct Tile) {
    prev->dir,
    NONE,
    {
      prev->rect.x + (dir.x * TILE_SIZE),
      prev->rect.y + (dir.y * TILE_SIZE),
      TILE_SIZE,
      TILE_SIZE
    },
    WHITE
  };
}

void paint(struct State *state, SDL_Renderer *renderer) {
  for (int i = 0; i < state->index; i++) {
    struct Tile *tile = &state->snake[i];

    SDL_Color col = tile->colour;

    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(renderer, &tile->rect);
  }

  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
  SDL_RenderClear(renderer);
}

bool loop(struct Window *window, struct State *state) {
  struct Tile *food = &state->snake[0];
  struct Tile *head = &state->snake[1];
  SDL_Event event;

  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return false;
    }

    handle_event(head, &event);
  }

  if (is_next_frame(&state->tick)) {
    if (positions_equal(&head->rect, &food->rect)) {
      eat_food(state, food);
    }

    update_positions(state);
  }

  paint(state, window->renderer);

  return true;
}
