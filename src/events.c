#include "events.h"
#include "tile.h"
#include "window.h"
#include <stdbool.h>

// void exec_key_press(Events *events, Map *map) {
//   char key = (char) events->sdl_event.key.keysym.sym;
//   char *keys = "wsad";
//   char *pos = strchr(keys, key);
//
//   events->key_event.user.data1 = NULL;
//
//   if (map != NULL && pos != NULL) {
//     events->key_event.user.data1 = (void *) (pos - keys);
//     events->key_event.user.data2 = (void *) map;
//
//     SDL_PushEvent(&events->key_event);
//   }
// }
//
// void exec_event(Events *events, Map *map) {
//   // void *data = sdl_event->user.data1;
//   int *direction;
//   Tile *tile;
//
//   switch (events->sdl_event.type) {
//   case SDL_QUIT:
//     return exit(0);
//   case SDL_KEYUP:
//     exec_key_press(events, NULL);
//     break;
//   case SDL_USEREVENT:
//     direction = (int *) events->sdl_event.user.data1;
//     tile = map->tiles[map->head_pos.x][map->head_pos.y];
//
//     tile->direction = (*direction) + 1;
//     break;
//   }
// }
