#include "colours.h"
#include "tile.h"
#include "window.h"

// void paint_tile(Tile *tile) {
//   SDL_Color col = tile->colour;
//   Display *display = tile->map->display;
//
//   SDL_SetRenderDrawColor(display->renderer, col.r, col.g, col.b, col.a);
//   SDL_RenderFillRect(tile->map->display->renderer, &tile->rect);
// }
//
// void set_tile_movement(Tile *tile, int mx, int my) {
//   int x = tile->pos_x;
//   int y = tile->pos_y;
//   bool x_free = x + 1 < WIN_TILE_WIDTH && x - 1 >= 0;
//   bool y_free = y + 1 < WIN_TILE_HEIGHT && y - 1 >= 0;
//
//   if (x_free && y_free) {
//     if (tile->is_head) {
//       tile->map->head_pos.x = x + mx;
//       tile->map->head_pos.y = y + my;
//
//       tile->map->tiles[x + mx][y + my]->is_head = true;
//     }
//
//     tile->move_to_x = mx;
//     tile->move_to_y = my;
//     tile->is_head = false;
//   }
// }
//
// void direct_tile(int x, int y, Map *map) {
//   Tile *tile = map->tiles[x][y];
//
//   switch (tile->direction) {
//   case up:
//     set_tile_movement(tile, 0, -1);
//     break;
//   case down:
//     set_tile_movement(tile, 0, 1);
//     break;
//   case left:
//     set_tile_movement(tile, -1, 0);
//     break;
//   case right:
//     set_tile_movement(tile, 1, 0);
//     break;
//   default:
//     break;
//   }
// }
//
// void move_tile(int x, int y, Map *map) {
//   Tile *tile = map->tiles[x][y];
//
//   if (tile->direction > 0) {
//     int mtx = tile->move_to_x;
//     int mty = tile->move_to_y;
//     int dir = tile->direction;
//
//     Tile *new_tile = create_tile(x, y, tile->is_head, tile->map);
//     Tile *next_tile = map->tiles[x + mtx][y + mty];
//
//     free(tile);
//
//     map->tiles[x][y] = new_tile;
//
//     next_tile->colour = WHITE;
//     next_tile->direction = dir;
//   }
// }
