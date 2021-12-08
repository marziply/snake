#include <SDL2/SDL.h>
#include <stdbool.h>

struct Direction {
  int x;
  int y;
};

struct Tile {
  struct Direction dir;
  SDL_Rect *rect;
  SDL_Color colour;
};

// void paint_tile(struct Tile *tile);
//
// void move_tile(int x, int y, struct Map *map);
//
// void direct_tile(int x, int y, struct Map *map);
