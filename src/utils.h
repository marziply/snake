#define tile_foreach(t_name)\
  for (\
    struct Tile *t_name = state->snake;\
    tile < &state->snake[SNAKE_LENGTH];\
    tile++\
  )

#define tile_foreach_index_from(t_name, i_name, i_from)\
  struct Tile *t_name = &state->snake[i_from];\
  for (\
    int i_name = i_from;\
    i_name < state->index;\
    t_name++,\
    i_name++\
  )

#define tile_foreach_index(...) tile_foreach_index_from(__VA_ARGS__, 0)

int rand_range(int min, int max);
