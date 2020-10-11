#include <SDL2/SDL.h>

void print_error (char *c) {
  char *failed = " failed: %s\n";
  char *str = malloc(strlen(c) + strlen(failed));

  strcpy(str, c);
  strcat(str, failed);

  printf(str, SDL_GetError());

  free(str);
}

