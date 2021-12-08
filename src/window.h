#include <SDL2/SDL.h>

#define N_TILES 20
#define TILE_SIZE 25
#define WIN_TITLE "Snake"
#define WIN_SIZE (TILE_SIZE * (N_TILES + 1))

struct Window {
  SDL_Window *window;
  SDL_Renderer *renderer;
};

struct Window init_window();

SDL_Renderer *init_renderer();
