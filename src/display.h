#pragma once
#include <SDL2/SDL.h>

#define TILE_SIZE 25
#define WIN_TITLE "Snake"
#define WIN_TILE_WIDTH 20
#define WIN_TILE_HEIGHT 20
#define WIN_HEIGHT TILE_SIZE * WIN_TILE_WIDTH
#define WIN_WIDTH TILE_SIZE * WIN_TILE_HEIGHT

struct Display {
  SDL_Window *window;
  SDL_Renderer *renderer;
} display;

void create_display ();
