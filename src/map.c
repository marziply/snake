#include "map.h"
#include "colours.h"

void iterate_tiles (void *fn (int fx, int fy)) {
  for (int x = 0; x < WIN_TILE_WIDTH; x++) {
    for (int y = 0; y < WIN_TILE_HEIGHT; y++) {
      fn(x, y);
    }
  }
}

void create_tiles (int x, int y) {
  Tile *tile = create_tile(x, y, false);

  map.tiles[x][y] = tile;
}

void paint_tiles (int x, int y) {
  paint_tile(map.tiles[x][y]);
}

void create_map () {
  iterate_tiles((void *) &create_tiles);
};
