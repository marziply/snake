#include <stdlib.h>

int rand_range(int min, int max) {
  return rand() % (max + 1 - min) + min;
}
