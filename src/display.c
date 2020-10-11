#include "display.h"
#include "error.h"

void create_display () {
  struct Display d = {
    .window = SDL_CreateWindow(
      WIN_TITLE,
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WIN_HEIGHT,
      WIN_WIDTH,
      SDL_WINDOW_SHOWN
    ),
    .renderer = d.window
      ? SDL_CreateRenderer(
          d.window,
          -1,
          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        )
      : NULL
  };

  if (d.renderer == NULL) {
    print_error("Display");

    exit(1);
  }

  display = d;
}

