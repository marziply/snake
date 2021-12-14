#include "error.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    handle_error("SDL_Init", SDL_GetError);
  }

  if (TTF_Init() < 0) {
    handle_error("TTF_Init", TTF_GetError);
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
