#include "defs.h"

typedef struct {
  int x, y;
} HeadPos;

typedef struct Map {
  struct Tile *tiles[WIN_TILE_WIDTH][WIN_TILE_HEIGHT];
  struct Display *display;
  HeadPos head_pos;
} Map;

Map create_map (struct Display display);

void iter_tiles (void *fn (int fx, int fy, void *d), void *data);
void paint_tiles (int x, int y, Map *map);
