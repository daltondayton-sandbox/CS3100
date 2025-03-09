#include <pthread.h>
#include <stdio.h>

int x = 0;

void *my_thread_start(void *arg) {
  printf("Hello from the thread\n");
  x = 5;
  return NULL;
}

int main() {
  pthread_t thread;

  printf("Hello World\n");

  pthread_create(&thread, NULL, my_thread_start, NULL);
  pthread_join(thread, NULL);

  printf("Value of x from main: %i\n", x);

  return 0;
}
