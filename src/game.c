#include "colours.h"
#include "events.h"
#include "game.h"
#include "utils.h"
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

void update_score(struct Score *score, int value) {
  sprintf(score->value, "%d", value);

  score->surface = TTF_RenderText_Solid(
    score->font,
    score->value,
    WHITE
  );
  score->rect = (SDL_Rect) {
    5,
    0,
    score->surface->w,
    score->surface->h
  };
}

struct State init_state() {
  const char *path = "/Library/fonts/Arial Unicode.ttf";

  struct Tick tick = {
    0.0,
    150.0
  };

  struct Score score = {
    .font = TTF_OpenFont(path, 24)
  };

  update_score(&score, 0);

  struct State state = {
    {
      {
        NONE,
        NONE,
        rand_rect(&state),
        RED
      },
      {
        rand_dir(),
        NONE,
        rand_rect(&state),
        WHITE
      }
    },
    tick,
    score,
    2
  };

  return state;
}

bool is_next_frame(struct Tick *tick) {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), tick->target)) {
    tick->target = SDL_GetTicks() + tick->width;

    return true;
  }

  return false;
}

void update_positions(struct State *state) {
  tile_foreach_index(p_tile, p_index) {
    tile_foreach_index_from(c_tile, c_index, 2) {
      if ((p_index == 0) || (p_index == c_index)) {
        continue;
      }

      if (SDL_RectEquals(&p_tile->rect, &c_tile->rect)) {
        printf("Game over!\nPoints: %d\n", state->index - 2);

        exit(0);
      }
    }

    if (!dirs_equal(p_tile->next_dir, NONE)) {
      p_tile->dir = p_tile->next_dir;
      p_tile->next_dir = NONE;
    }

    if (p_index > 1) {
      struct Tile *prev = &state->snake[p_index - 1];

      p_tile->next_dir = prev->dir;
    }

    move_tile(p_tile->dir, &p_tile->rect);
  }
}

void eat_food(struct State *state, struct Tile *food) {
  struct Tile *prev = &state->snake[state->index - 1];
  struct Direction dir = inverse_dir(prev->dir);

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
  food->rect = rand_rect(state);

  update_score(&state->score, state->index - 2);

  if (state->tick.width > MIN_SPEED) {
    state->tick.width -= SPEED_MOD;
  }
}

void paint(struct State *state, SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
  SDL_RenderClear(renderer);

  for (int i = 0; i < state->index; i++) {
    struct Tile *tile = &state->snake[i];

    SDL_Color col = tile->colour;

    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(renderer, &tile->rect);
  }

  SDL_Texture *text_tex = SDL_CreateTextureFromSurface(
    renderer,
    state->score.surface
  );
  SDL_RenderCopy(renderer, text_tex, NULL, &state->score.rect);
  SDL_RenderPresent(renderer);
}

bool loop(struct Window *window, struct State *state) {
  struct Tile *food = &state->snake[0];
  struct Tile *head = &state->snake[1];
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return false;
    }

    handle_event(head, &event);
  }

  if (is_next_frame(&state->tick)) {
    if (SDL_RectEquals(&head->rect, &food->rect)) {
      eat_food(state, food);
    }

    update_positions(state);
  }

  paint(state, window->renderer);

  return true;
}
