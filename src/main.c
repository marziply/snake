#include "error.h"
#include "events.h"
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
  SDL_Event event;

  // Delay the app slightly so the ENTER event is not registered from
  // the terminal running the binary
  SDL_Delay(250);

  while (true) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        fclose(state.bin);

        return 0;
      }

      handle_event(&state, &event);
    }

    loop(&window, &state);
  }

  return 0;
}
