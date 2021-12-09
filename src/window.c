#include "error.h"
#include "window.h"

struct Window init_window() {
  SDL_Window *sdl_window = SDL_CreateWindow(
    WIN_TITLE,
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WIN_SIZE,
    WIN_SIZE,
    SDL_WINDOW_OPENGL
  );

  struct Window window = {
    .window = sdl_window,
    .renderer = sdl_window ? init_renderer(sdl_window) : NULL,
  };

  if(window.renderer == NULL) {
    print_error("Window");

    exit(1);
  }

  return window;
}

SDL_Renderer *init_renderer(SDL_Window *window) {
  return SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
}
