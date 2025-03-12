#include "paged_mem.h"
#include <stdio.h>
#include <stdlib.h>

void print_usage(const char *progname) {
  fprintf(stderr, "Usage: %s <memory_file>\n", progname);
}

int main(int argc, char *argv[]) {
  // Check if the memory file argument was provided.
  if (argc < 2) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  // If the argument is provided, store it for later use.
  char *memory_file = argv[1];
  printf("Memory file provided: %s\n", memory_file);

  return EXIT_SUCCESS;
}

