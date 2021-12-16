#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int rand_range(int min, int max) {
  return rand() % (max + 1 - min) + min;
}

char *int_to_str(int value) {
  char *result = calloc(12, sizeof(char));

  sprintf(result, "%i", value);

  return result;
}

FILE *open_bin(const char *mode) {
  size_t len = 128;
  char path[len];

  getcwd(path, len);
  strcat(path, "/snake");

  FILE *bin = fopen(path, mode);

  // Set initial index of file to the last byte
  fseek(bin, -1, SEEK_END);

  return bin;
}
