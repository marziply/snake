#include "colours.h"
#include "game.h"
#include "utils.h"
#include <stdio.h>
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
  FILE *bin = open_bin("r");

  // Initial fonts with varying sizes for their respective locations within
  // the game
  TTF_Font *m_font = TTF_OpenFont(FONT_PATH, M_FONT_SIZE);
  TTF_Font *g_font = TTF_OpenFont(FONT_PATH, G_FONT_SIZE);

  // Initial high score value derived from the last byte of the binary, acting
  // as state without having to write to a separate file
  char *high_score = int_to_str(get_high_score(bin));

  struct Tick tick = init_tick();

  struct State state = {
    .bin = bin,
    .mode = MENU,
    .select = PLAY,
    .tick = tick,
    create_text("0", TEXT_PADDING, WIN_SIZE, g_font),
    create_text(high_score, 30, WIN_SIZE - 50, m_font),
    create_text(tick_to_str(&tick), WIN_SIZE, WIN_SIZE, g_font),
    {
      create_text("Play", 30, 30, m_font),
      create_text("Exit", 30, 100, m_font),
    }
  };

  // Sets initial tile positions and text colours
  reset_tiles(&state);
  set_text_colour(state.menu_items, RED);

  return state;
}

char *tick_to_str(struct Tick *tick) {
  // 12 bytes for the speed number
  // 12 bytes for the total number
  // 8 bytes for the " / "
  char *result = calloc(32, sizeof(char));
  char *speed = int_to_str(MAX_SPEED - tick->width);

  strcpy(result, speed);
  strcat(result, " / ");
  strcat(result, int_to_str(MAX_SPEED - MIN_SPEED));

  return result;
}

int get_high_score(FILE *file) {
  int score = fgetc(file);

  fseek(file, -1, SEEK_END);

  return score;
}

void set_high_score(FILE *file, int score) {
  fputc(score, file);
  fseek(file, -1, SEEK_END);
}

void reset_tiles(struct State *state) {
  // Inital array of tiles for the snake, with randomly set X and Y positions
  // and randomly set directions
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

  state->speed.rect.x = WIN_SIZE;
  state->tail_index = 2;
  state->tick = init_tick();

  // Clear the current state of snake tiles and then move the initial
  // state above into it
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
  int score = state->tail_index - 2;

  // Sets the last byte of the binary to the current score value if it beats
  // the current high score value stored there
  if (score > get_high_score(state->bin)) {
    // set_high_score(state->bin, score);
  }

  state->mode = MENU;

  reset_tiles(state);
}

void update_text_values(struct State *state) {
  // No need to store the high score anywhere as it can be inferred from
  // the tail index minus the food and head tiles
  int current_score = state->tail_index - 2;
  int high_score = get_high_score(state->bin);

  set_text_value(&state->current_score, int_to_str(current_score));
  set_text_value(&state->speed, tick_to_str(&state->tick));

  // Update the high score text value on the menu screen only if it beats
  // the current high score
  if (current_score > high_score) {
    set_text_value(&state->high_score, int_to_str(current_score));
  }
}

void update_positions(struct State *state) {
  // Iterate over all snake tiles to update their current positions to their
  // respective next_dir values
  tile_foreach_index(p) {
    // Check for collisions with other snake tiles
    tile_foreach_index_from(c, 2) {
      // Skips the iteration if the tile matches the tile in the parent loop
      // or if it is equal to 0, which will always be the index of the food
      // tile
      if ((p_index == 0) || (p_index == c_index)) {
        continue;
      }

      // Check for any collisions by check the equality between the parent
      // loop tile and the current loop tile
      if (SDL_RectEquals(&p_tile->rect, &c_tile->rect)) {
        end_game(state);
      }
    }

    // Only move the tile if it currently has a direction set, which prevents
    // the food tile from moving anywhere
    if (!dirs_equal(p_tile->next_dir, NONE)) {
      p_tile->dir = p_tile->next_dir;
      p_tile->next_dir = NONE;
    }

    // Updates the next_dir value only if it isn't the head tile, which always
    // has an index value of 0
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

  // Appends a new snake tile to the end of the snake, following the direction
  // of the previous tail tile
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

  // Limits the speed from increasing past MIN_SPEED so the game remains
  // playable
  if (state->tick.width > MIN_SPEED) {
    state->tick.width -= SPEED_MOD;
  }

  update_text_values(state);
}

void paint_menu(struct State *state, SDL_Renderer *renderer) {
  // Paint each menu item
  text_foreach(v, state->menu_items, N_MENU_ITEMS) {
    render_text(v_text, renderer);
  }

  render_text(&state->high_score, renderer);
}

void paint_game(struct State *state, SDL_Renderer *renderer) {
  // Paint each snake tile
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

void loop(struct Window *window, struct State *state) {
  // Easy "shortcuts" to the food and head tiles
  struct Tile *food = &state->snake[0];
  struct Tile *head = &state->snake[1];

  // Moves the tiles only on each subsequent new "frame", as configured
  // via the tick value on state
  if (is_next_frame(&state->tick) && (state->mode == GAME)) {
    if (SDL_RectEquals(&head->rect, &food->rect)) {
      eat_food(state, food);
    }

    update_positions(state);
  }

  paint(state, window->renderer);
}
