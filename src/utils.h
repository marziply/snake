#define tile_foreach(t_name)\
  for (\
    struct Tile *t_name ## _tile = state->snake;\
    t_name ## _tile < &state->snake[SNAKE_LENGTH];\
    t_name ## _tile++\
  )

#define tile_foreach_index_from(t_name, i_from)\
  struct Tile *t_name ## _tile = &state->snake[i_from];\
  for (\
    int t_name ## _index = i_from;\
    t_name ## _index < state->index;\
    t_name ## _tile++,\
    t_name ## _index++\
  )

#define tile_foreach_index(...) tile_foreach_index_from(__VA_ARGS__, 0)

int rand_range(int min, int max);
