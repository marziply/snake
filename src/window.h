#include <SDL2/SDL.h>

#define N_TILES 20
#define TILE_SIZE 25
#define WIN_TITLE "Snake"
#define WIN_SIZE (TILE_SIZE * (N_TILES + 1))
#define WIN_EDGE (WIN_SIZE - TILE_SIZE)
#define TAIL_SIZE ((size_t)(sizeof(struct Tile) * pow(N_TILES, 2)))

struct Window {
  SDL_Window *window;
  SDL_Renderer *renderer;
};

struct Window init_window();

SDL_Renderer *init_renderer();
