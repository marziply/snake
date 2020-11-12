#include "display.h"
#include "error.h"
#include "events.h"
#include "map.h"
#include <SDL2/SDL.h>
#include <stdio.h>

void init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("error: %s\n", SDL_GetError());

    exit(1);
  }
}

int main(int argc, char **argv) {
  int i = SDL_Init(SDL_INIT_VIDEO);

  if (i != 0) {
    printf("error: %s", SDL_GetError());
  }

  init();

  Display display = create_display();
  Map map = create_map(display);

  poll(map);

  SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                   -1, -1, SDL_WINDOW_OPENGL);

  SDL_Event event;

  SDL_PollEvent(&event);

  return 0;
}
