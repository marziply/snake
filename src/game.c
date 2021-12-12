#include "colours.h"
#include "events.h"
#include "game.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>

struct Tick init_tick() {
  return (struct Tick) {
    0.0,
    MAX_SPEED
  };
}

struct State init_state() {
  TTF_Font *m_font = TTF_OpenFont(FONT_PATH, M_FONT_SIZE);
  TTF_Font *g_font = TTF_OpenFont(FONT_PATH, G_FONT_SIZE);

  struct Tick tick = init_tick();

  struct State state = {
    .mode = MENU,
    .select = PLAY,
    .tick = tick,
    create_text("0", TEXT_PADDING, WIN_SIZE, g_font),
    create_text(tick_to_str(&tick), WIN_SIZE, WIN_SIZE, g_font),
    {
      create_text("Play", 30, 30, m_font),
      create_text("Exit", 30, 100, m_font),
    }
  };

  reset_tiles(&state);
  set_text_colour(state.menu_items, RED);

  return state;
}

char *tick_to_str(struct Tick *tick) {
  char *result = calloc(32, sizeof(char));
  char *speed = int_to_str(MAX_SPEED - tick->width);

  strcpy(result, speed);
  strcat(result, " / ");
  strcat(result, int_to_str(MAX_SPEED - MIN_SPEED));

  return result;
}

void reset_tiles(struct State *state) {
  struct Tile tiles[2] = {
    {
      NONE,
      NONE,
      rand_rect(state, 0),
      RED
    },
    {
      rand_dir(),
      NONE,
      rand_rect(state, 1),
      WHITE
    }
  };

  state->tail_index = 2;
  state->tick = init_tick();

  memset(state->snake, 0, SNAKE_SIZE);
  memmove(state->snake, tiles, 2 * sizeof(struct Tile));

  update_text_values(state);
}

bool is_next_frame(struct Tick *tick) {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), tick->target)) {
    tick->target = SDL_GetTicks() + tick->width;

    return true;
  }

  return false;
}

void end_game(struct State *state) {
  printf("Game over!\nPoints: %i\n", state->tail_index - 2);

  state->mode = MENU;

  reset_tiles(state);
}

void update_text_values(struct State *state) {
  set_text_value(&state->current_score, int_to_str(state->tail_index - 2));
  set_text_value(&state->speed, tick_to_str(&state->tick));
}

void update_positions(struct State *state) {
  tile_foreach_index(p) {
    tile_foreach_index_from(c, 2) {
      if ((p_index == 0) || (p_index == c_index)) {
        continue;
      }

      if (SDL_RectEquals(&p_tile->rect, &c_tile->rect)) {
        end_game(state);
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
  struct Tile *prev = &state->snake[state->tail_index - 1];
  struct Direction dir = inverse_dir(prev->dir);

  state->snake[state->tail_index++] = (struct Tile) {
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
  food->rect = rand_rect(state, 0);

  if (state->tick.width > MIN_SPEED) {
    state->tick.width -= SPEED_MOD;
  }

  update_text_values(state);
}

void paint_menu(struct State *state, SDL_Renderer *renderer) {
  text_foreach(v, state->menu_items, N_MENU_ITEMS) {
    render_text(v_text, renderer);
  }
}

void paint_game(struct State *state, SDL_Renderer *renderer) {
  tile_foreach(v) {
    render_tile(v_tile, renderer);
  }

  render_text(&state->current_score, renderer);
  render_text(&state->speed, renderer);
}

void paint(struct State *state, SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
  SDL_RenderClear(renderer);

  switch (state->mode) {
  case MENU:
    paint_menu(state, renderer);
    break;
  case GAME:
    paint_game(state, renderer);
    break;
  }

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

    handle_event(state, &event);
  }

  if ((state->mode == GAME) && is_next_frame(&state->tick)) {
    if (SDL_RectEquals(&head->rect, &food->rect)) {
      eat_food(state, food);
    }

    update_positions(state);
  }

  paint(state, window->renderer);

  return true;
}
