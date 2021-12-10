#include "error.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Error: %s\n", SDL_GetError());

    exit(1);
  }

  srand(time(0));

  Snake *snake = calloc(SNAKE_SIZE, sizeof(struct Tile));
  struct Window window = init_window();
  struct State state = init_state(snake);

  while (true) {
    if (!loop(&window, &state)) {
      break;
    }
  }

  return 0;
}
