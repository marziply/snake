#include <SDL2/SDL.h>
#include <stdio.h>
#include "display.h"
#include "map.h"
#include "events.h"
#include "error.h"

void init () {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    print_error("Init");

    exit(1);
  }
}

int main (int argc, char **argv) {
  init();

  create_display();
  create_map();

  poll();

  return 0;
}
