#include <stdio.h>

int main(int argc, char **argv) {
  if (argc > 1) {
    printf("Usage: %s\nThis program does not accept command line parameters.\n",
           argv[0]);
    return 1;
  }

  return 0;
}

