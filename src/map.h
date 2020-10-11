#pragma once
#include "tile.h"

typedef struct Map Map;
struct Map {
  Tile *tiles[WIN_TILE_WIDTH][WIN_TILE_HEIGHT];
} map;
struct HeadPos {
  int x, y;
} head_pos;

void iter_tiles (void *fn (int fx, int fy));
void paint_tiles (int x, int y);
void create_map ();
