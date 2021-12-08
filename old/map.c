#include "map.h"
#include "colours.h"
#include "tile.h"
#include <stdbool.h>

void iter_tiles(void *fn(int fx, int fy, void *d), void *data) {
  for (int x = 0; x < WIN_TILE_WIDTH; x++) {
    for (int y = 0; y < WIN_TILE_HEIGHT; y++) {
      fn(x, y, data);
    }
  }
}

// void create_tiles(int x, int y, Map *map) {
//   Tile *tile = create_tile(x, y, false, map);
//
//   map->tiles[x][y] = tile;
// }

void paint_tiles(int x, int y) {
  // Tile *tile = map->tiles[x][y];

  // paint_tile(tile);
}
