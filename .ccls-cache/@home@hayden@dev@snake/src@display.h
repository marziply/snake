#include <SDL2/SDL.h>

typedef struct Display {
  struct Map *map;
  SDL_Window *window;
  SDL_Renderer *renderer;
} Display;

Display create_display ();
