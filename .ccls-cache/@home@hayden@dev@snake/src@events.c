#include <stdbool.h>
#include "events.h"
#include "colours.h"
#include "display.h"
#include "map.h"
#include "tile.h"

void exec_key_press (Events *events, Map *map) {
  char key = (char) events->sdl_event.key.keysym.sym;
  char *keys = "wsad";
  char *pos = strchr(keys, key);

  events->key_event.user.data1 = NULL;

  if (map != NULL && pos != NULL) {
    events->key_event.user.data1 = (void *) (pos - keys);
    events->key_event.user.data2 = (void *) map;

    SDL_PushEvent(&events->key_event);
  }
}

void exec_event (Events *events, Map *map) {
  // void *data = sdl_event->user.data1;
  int *direction;
  Tile *tile;

  switch (events->sdl_event.type) {
  case SDL_QUIT:
    return exit(0);
  // case SDL_KEYUP:
  //   exec_key_press(events, NULL);
  //   break;
  // case SDL_USEREVENT:
  //   direction = (int *) events->sdl_event.user.data1;
  //   tile = map->tiles[map->head_pos.x][map->head_pos.y];
  // 
  //   tile->direction = (*direction) + 1;
  //   break;
  }
}

void update () {
  iter_tiles((void *) &direct_tile, NULL);
  iter_tiles((void *) &move_tile, NULL);
}

void poll (Map map) {
  double time_since = 0.0;
  Events events;
  Display *display = map.display;

  // map.head_pos.x = rand() % WIN_TILE_WIDTH;
  // map.head_pos.y = rand() % WIN_TILE_HEIGHT;
  // 
  // Tile *tile = map.tiles[map.head_pos.x][map.head_pos.y];
  // 
  // printf("tile: %p\n", (void *) tile);
  // 
  // tile->is_head = true;
  // printf("head: %d\n", tile->is_head);
  // tile->colour = WHITE;
  // tile->direction = (rand() % 4) + 1;
  // 
  // events.key_event.type = SDL_RegisterEvents(1);

  while (true) {
    // if (time_since >= 1.0) {
    //   time_since = 0.0;
    // 
    //   update();
    // }

    if (SDL_PollEvent(&events.sdl_event)) {
      exec_event(&events, &map);
    }

    // time_since += TICK;

    // iter_tiles((void *) &paint_tiles, NULL);

    // SDL_RenderPresent(map.display->renderer);
    // 
    // SDL_SetRenderDrawColor(display->renderer, BLACK.r, BLACK.g, BLACK.b, 255);
    // SDL_RenderClear(display->renderer);
    // 
    // SDL_Delay(TICK);
  }
}
