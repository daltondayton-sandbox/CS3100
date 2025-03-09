#include <stdio.h>
#include <unistd.h>

int main() {
  int x = 0;
  int y = 0;
  int z = 0;

  pid_t pid;

  printf("Hello World\n");

  x = 5;
  y += 2;

  pid = fork();

  if (pid == 0) { // Child
    x += 3;
    y += 3;
    z += 3;

    printf("Hello from the child\n");
    printf("Child Forked PID Value = %i\n", pid);
    printf("Child PID: %i\n", getpid());
    printf("Child Values: %i, %i, %i\n", x, y, z);
  } else if (pid < 0) { // Error forking

  } else { // Parent
    x += 2;
    y += 2;
    z += 2;

    printf("Hello from the parent\n");
    printf("Parent Forked PID Value = %i\n", pid);
    printf("Parent PID: %i\n", getpid());
    printf("Parent Values: %i, %i, %i\n", x, y, z);
  }

  return 0;
}
