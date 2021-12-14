#include <SDL2/SDL.h>

void handle_error(char *c, const char *(callback) ()) {
  char *failed = " failed: %s\n";
  char *str = malloc(strlen(c) + strlen(failed) + 1);

  strcpy(str, c);
  strcat(str, failed);

  printf(str, callback());

  exit(1);
}
