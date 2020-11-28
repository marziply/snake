#include "defs.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

enum Direction {
  none,
  up,
  down,
  left,
  right,
};

typedef struct Tile {
  int move_to_x, move_to_y;
  int pos_x, pos_y;
  bool is_head;
  enum Direction direction;
  struct Map *map;
  SDL_Rect rect;
  SDL_Color colour;
  void *paint;
  // void *paint (Tile *tile);
} Tile;

Tile *create_tile(int x, int y, bool is_head, struct Map *map);

void paint_tile(struct Tile *tile);
void move_tile(int x, int y, struct Map *map);
void direct_tile(int x, int y, struct Map *map);
