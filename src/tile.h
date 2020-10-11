#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"

enum Direction {
  none,
  up,
  down,
  left,
  right
};

typedef struct {
  int move_to_x, move_to_y;
  int pos_x, pos_y;
  bool is_head;
  enum Direction direction;
  SDL_Rect rect;
  SDL_Color colour;
} Tile;

Tile *create_tile (int x, int y, bool is_head);

void paint_tile (Tile *tile);
void move_tile (int x, int y);
void direct_tile (int x, int y);
