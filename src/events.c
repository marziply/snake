#include <stdbool.h>
#include "events.h"
#include "colours.h"

void exec_key_press (SDL_Event *sdl_event) {
  char key = (char) sdl_event->key.keysym.sym;
  char *keys = "wsad";
  char *pos = strchr(keys, key);

  key_event.user.data1 = NULL;

  if (pos != NULL) {
    key_event.user.data1 = (void *) (pos - keys);

    SDL_PushEvent(&key_event);
  }
}

void exec_event (SDL_Event *sdl_event) {
  void *data = sdl_event->user.data1;

  switch (sdl_event->type) {
  case SDL_QUIT:
    return exit(0);
  case SDL_KEYUP:
    exec_key_press(sdl_event);
    break;
  case SDL_USEREVENT:
    map.tiles[head_pos.x][head_pos.y]->direction = (int) data + 1;
    break;
  }
}

void update () {
  iter_tiles((void *) &direct_tile);
  iter_tiles((void *) &move_tile);
}

void poll () {
  double time_since = 0.0;

  head_pos.x = rand() % WIN_TILE_WIDTH;
  head_pos.y = rand() % WIN_TILE_HEIGHT;

  Tile *tile = map.tiles[head_pos.x][head_pos.y];

  tile->is_head = true;
  tile->colour = WHITE;
  tile->direction = (rand() % 4) + 1;

  key_event.type = SDL_RegisterEvents(1);

  while (true) {
    if (time_since >= 1.0) {
      time_since = 0.0;

      update();
    }
    if (SDL_PollEvent(&sdl_event)) exec_event(&sdl_event);

    time_since += TICK;

    iter_tiles((void *) &paint_tiles);

    SDL_RenderPresent(display.renderer);

    SDL_SetRenderDrawColor(display.renderer, BLACK.r, BLACK.g, BLACK.b, 255);
    SDL_RenderClear(display.renderer);

    SDL_Delay(TICK);
  }
}
