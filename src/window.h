#include <math.h>
#include <SDL2/SDL.h>

#define N_TILES 20
#define TILE_SIZE 25
#define SPEED_MOD 5.0
#define WIN_TITLE "Snake"
#define WIN_SIZE (TILE_SIZE * (N_TILES + 1))
#define WIN_EDGE (WIN_SIZE - TILE_SIZE)
#define SNAKE_LENGTH (N_TILES * N_TILES)
#define SNAKE_SIZE ((size_t) (sizeof(struct Tile) * SNAKE_LENGTH))

struct Window {
  SDL_Window *window;
  SDL_Renderer *renderer;
};

struct Window init_window();

SDL_Renderer *init_renderer();
