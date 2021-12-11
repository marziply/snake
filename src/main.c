#include "error.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error: %s\n", SDL_GetError());

    exit(1);
  }

  if (TTF_Init() < 0) {
    printf("Error: %s\n", TTF_GetError());

    exit(1);
  }

  srand(time(0));

  struct Window window = init_window();
  struct State state = init_state();

  while (true) {
    if (!loop(&window, &state)) {
      break;
    }
  }

  return 0;
}
