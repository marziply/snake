#include "colours.h"
#include "text.h"
#include "window.h"
#include <string.h>

struct Text create_text(char *value, int x, int y, TTF_Font *font) {
  struct Text text = {
    .font = font,
    .colour = WHITE,
    .rect = { x, y }
  };

  strcpy(text.value, value);
  set_text_value(&text, value);

  return text;
}

char *int_to_str(int value) {
  char *result = calloc(12, sizeof(char));

  sprintf(result, "%i", value);

  return result;
}

void render_text(struct Text *text, SDL_Renderer *renderer) {
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text->surface);
  SDL_RenderCopy(renderer, texture, NULL, &text->rect);
}

void set_text_colour(struct Text *text, SDL_Color colour) {
  SDL_Surface *surface = TTF_RenderText_Solid(text->font, text->value, colour);

  text->surface = surface;
}

void set_text_value(struct Text *text, char *value) {
  SDL_Surface *surface = TTF_RenderText_Solid(text->font, value, text->colour);
  int clip_x = text->rect.x + surface->w;
  int new_x = clip_x - (WIN_SIZE - TEXT_PADDING);

  if (clip_x >= WIN_SIZE) {
    text->rect.x -= new_x;
  }

  text->rect.w = surface->w;
  text->rect.h = surface->h;
  text->surface = surface;
}
