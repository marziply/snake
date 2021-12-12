#include <SDL2/SDL_ttf.h>

#define FONT_PATH "./assets/font.ttf"
#define FONT_SIZE 24
#define TEXT_PADDING 5

struct Text {
  char value[32];
  TTF_Font *font;
  SDL_Surface *surface;
  SDL_Rect rect;
};

struct Text create_text(char *value, int x, int y, TTF_Font *font);

char *int_to_str(int value);

void set_text_value(struct Text *text, char *value);

void render_text(struct Text *text, SDL_Renderer *renderer);
