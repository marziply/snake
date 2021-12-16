#include <stdio.h>

#define text_foreach(var_name, array_name, len)\
  for (\
    struct Text *var_name ## _text = array_name;\
    var_name ## _text < &array_name[len];\
    var_name ## _text++\
  )

#define tile_foreach(var_name)\
  for (\
    struct Tile *var_name ## _tile = state->snake;\
    var_name ## _tile < &state->snake[SNAKE_LENGTH];\
    var_name ## _tile++\
  )

#define tile_foreach_index_from(var_name, index_from)\
  struct Tile *var_name ## _tile = &state->snake[index_from];\
  for (\
    int var_name ## _index = index_from;\
    var_name ## _index < state->tail_index;\
    var_name ## _tile++,\
    var_name ## _index++\
  )

#define tile_foreach_index(...) tile_foreach_index_from(__VA_ARGS__, 0)

int rand_range(int min, int max);

char *int_to_str(int value);

FILE *open_bin();
