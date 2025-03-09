#include "basic_math.h"
#include <stdio.h>

int main() {
  int x, y;
  printf("Enter a number:");
  scanf("%d", &x);

  printf("Enter a number:");
  scanf("%d", &y);

  printf("%d + %d = %d\n", x, y, add(x, y));

  return 0;
}
