#include "game.h"
#include "colours.h"
#include "events.h"

int randr(int min, int max) {
  return rand() % (max + 1 - min) + min;
}

struct State init_state() {
  int head_dx = randr(-1, 1);
  int head_dy = (1 ^ abs(head_dx)) * ((randr(0, 1) * 2) - 1);
  size_t tail_size = sizeof(struct Tile) * pow(N_TILES, 2);
  SDL_Rect rect = {
    .x = randr(0, N_TILES) * TILE_SIZE,
    .y = randr(0, N_TILES) * TILE_SIZE,
    .w = TILE_SIZE,
    .h = TILE_SIZE,
  };
  struct Direction dir = {
    .x = head_dx,
    .y = head_dy,
  };
  struct Tile head = {
    .dir = dir,
    .rect = &rect,
    .colour = WHITE,
  };
  struct Tick tick = {
    .width = 30.0,
    .total = 0.0,
    .step = 0.5,
  };

  struct State state = {
    .tail = calloc(sizeof(struct Tile), tail_size),
    .head = &head,
    .tick = &tick,
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

bool is_moveable(int x, int y) {
  int edge = WIN_SIZE - TILE_SIZE;

  return y != 0 && x != 0 && x != edge && y != edge;
}

void move(SDL_Rect *rect, struct Direction dir) {
  if (is_moveable(rect->x, rect->y)) {
    rect->x += dir.x * TILE_SIZE;
    rect->y += dir.y * TILE_SIZE;
  }
}

void paint(SDL_Renderer *renderer, struct State *state) {
  // iter_tiles((void *) &direct_tile, map);
  // iter_tiles((void *) &move_tile, map);

  // for (int x = 0; x < WIN_TILE_WIDTH; x++) {
  //   for (int y = 0; y < WIN_TILE_WIDTH; y++) {
  //     struct Tile tile = container->state.segments[x][y];
  //   }
  // }

  SDL_Color col = state->head->colour;

  SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
  SDL_RenderFillRect(renderer, state->head->rect);
}

bool loop(struct Window *window, struct State *state) {
  struct Events events;

  // events.key_event.type = SDL_RegisterEvents(1);

  if (is_next_frame(state->tick)) {
    move(state->head->rect, state->head->dir);
  }

  if (SDL_PollEvent(&events.sdl_event)) {
    // exec_event(&events, &map);
    if (events.sdl_event.type == SDL_QUIT) {
      return false;
    }
  }

  paint(window->renderer, state);

  // iter_tiles((void *) &paint_tiles, &map);

  SDL_RenderPresent(window->renderer);

  SDL_SetRenderDrawColor(window->renderer, BLACK.r, BLACK.g, BLACK.b, 255);
  SDL_RenderClear(window->renderer);

  SDL_Delay(next_tick(state->tick));

  return true;
}
