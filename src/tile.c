#include "tile.h"
#include "colours.h"
#include "map.h"

Tile *create_tile (int x, int y, bool is_head) {
  SDL_Rect rect = {
    .x = x * TILE_SIZE,
    .y = y * TILE_SIZE,
    .w = TILE_SIZE,
    .h = TILE_SIZE
  };

  Tile *tile = (Tile *) malloc(sizeof(Tile));

  tile->pos_x = x;
  tile->pos_y = y;
  tile->move_to_x = 0;
  tile->move_to_y = 0;
  tile->is_head = is_head;
  tile->direction = none;
  tile->rect = rect;
  tile->colour = BLACK;

  return tile;
}

void paint_tile (Tile *tile) {
  SDL_Color colour = tile->colour;

  SDL_SetRenderDrawColor(
    display.renderer,
    colour.r,
    colour.g,
    colour.b,
    colour.a
  );
  SDL_RenderFillRect(display.renderer, &tile->rect);
}

void set_tile_movement (Tile *tile, int mx, int my) {
  int x = tile->pos_x;
  int y = tile->pos_y;
  bool x_free = x + 1 < WIN_TILE_WIDTH && x - 1 >= 0;
  bool y_free = y + 1 < WIN_TILE_HEIGHT && y - 1 >= 0;

  if (x_free && y_free){
    if (tile->is_head) {
      head_pos.x = x + mx;
      head_pos.y = y + my;

      map.tiles[x + mx][y + my]->is_head = true;
    }

    tile->move_to_x = mx;
    tile->move_to_y = my;
    tile->is_head = false;
  }
}

void direct_tile (int x, int y) {
  Tile *tile = map.tiles[x][y];

  switch (tile->direction) {
  case up:
    set_tile_movement(tile, 0, -1);
    break;
  case down:
    set_tile_movement(tile, 0, 1);
    break;
  case left:
    set_tile_movement(tile, -1, 0);
    break;
  case right:
    set_tile_movement(tile, 1, 0);
    break;
  default:
    break;
  }
}

void move_tile (int x, int y) {
  Tile *tile = map.tiles[x][y];

  if (tile->direction > 0) {
    int mtx = tile->move_to_x;
    int mty = tile->move_to_y;
    int dir = tile->direction;

    Tile *new_tile = create_tile(x, y, tile->is_head);

    free(tile);

    map.tiles[x][y] = new_tile;

    map.tiles[x + mtx][y + mty]->colour = WHITE;
    map.tiles[x + mtx][y + mty]->direction = dir;
  }
}