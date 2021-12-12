#include "colours.h"
#include "events.h"
#include "game.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>

char *tick_to_str(struct Tick *tick) {
  char *result = calloc(32, sizeof(char));
  char *speed = int_to_str(MAX_SPEED - tick->width);

  strcpy(result, speed);
  strcat(result, " / ");
  strcat(result, int_to_str(MAX_SPEED - MIN_SPEED));

  return result;
}

struct State init_state() {
  TTF_Font *font = TTF_OpenFont(FONT_PATH, FONT_SIZE);

  struct Tick tick = {
    0.0,
    MAX_SPEED
  };

  struct Text current_score = create_text(
    "0",
    TEXT_PADDING,
    WIN_SIZE - TEXT_PADDING,
    font
  );
  struct Text speed = create_text(
    tick_to_str(&tick),
    WIN_SIZE,
    WIN_SIZE - TEXT_PADDING,
    font
  );

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
    current_score,
    speed,
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

void end_game(int points) {
  printf("Game over!\nPoints: %i\n", points);

  exit(0);
}

void update_positions(struct State *state) {
  tile_foreach_index(p) {
    tile_foreach_index_from(c, 2) {
      if ((p_index == 0) || (p_index == c_index)) {
        continue;
      }

      if (SDL_RectEquals(&p_tile->rect, &c_tile->rect)) {
        end_game(state->index - 2);
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

  if (state->tick.width > MIN_SPEED) {
    state->tick.width -= SPEED_MOD;
  }

  set_text_value(&state->current_score, int_to_str(state->index - 2));
  set_text_value(&state->speed, tick_to_str(&state->tick));
}

void paint(struct State *state, SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
  SDL_RenderClear(renderer);

  tile_foreach(v) {
    render_tile(v_tile, renderer);
  }

  render_text(&state->current_score, renderer);
  render_text(&state->speed, renderer);

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
