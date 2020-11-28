#include "display.h"
#include "defs.h"
#include "error.h"

Display create_display() {
  Display display = {
    .window = SDL_CreateWindow(WIN_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        -1,
        -1,
        SDL_WINDOW_OPENGL),
    .renderer = display.window
                    ? SDL_CreateRenderer(display.window,
                          -1,
                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
                    : NULL,
  };

  if (display.renderer == NULL) {
    print_error("Display");

    exit(1);
  }

  return display;
}
