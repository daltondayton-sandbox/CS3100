#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *function1();
void *function2();
void *function3();

pthread_mutex_t mutex1, mutex2, mutex3;

int main() {
  pthread_mutex_init(&mutex1, NULL);
  pthread_mutex_init(&mutex2, NULL);
  pthread_mutex_init(&mutex3, NULL);
  pthread_t f_one, f_two, f_three;
  pthread_create(&f_one, NULL, function1, NULL);
  pthread_create(&f_two, NULL, function2, NULL);
  pthread_create(&f_three, NULL, function3, NULL);
  pthread_join(f_one, NULL);
  pthread_join(f_two, NULL);
  pthread_join(f_three, NULL);
  printf("Application Complete\n");
}

void *function1() {
  // Acquire mutex1
  pthread_mutex_lock(&mutex1);
  printf("Thread 1 acquired mutex1\n");
  sleep(1);

  // Wait for mutex2
  printf("Thread 1 waiting for mutex2\n");
  pthread_mutex_lock(&mutex2);
  printf("Thread 1 acquired mutex2\n");

  // Release mutexes
  pthread_mutex_unlock(&mutex2);
  printf("Thread 1 released mutex2\n");
  pthread_mutex_unlock(&mutex1);
  printf("Thread 1 released mutex1\n");

  return NULL;
}

void *function2() {
  // Acquire mutex2
  pthread_mutex_lock(&mutex2);
  printf("Thread 2 acquired mutex2\n");
  sleep(1);

  // Wait for mutex3
  printf("Thread 2 waiting for mutex3\n");
  pthread_mutex_lock(&mutex3);
  printf("Thread 2 acquired mutex3\n");

  // Release mutexes
  pthread_mutex_unlock(&mutex3);
  printf("Thread 2 released mutex3\n");
  pthread_mutex_unlock(&mutex2);
  printf("Thread 2 released mutex2\n");

  return NULL;
}

void *function3() {
  // Acquire mutex3
  pthread_mutex_lock(&mutex3);
  printf("Thread 3 acquired mutex3\n");
  sleep(1);

  // Wait for mutex1
  printf("Thread 3 waiting for mutex1\n");
  pthread_mutex_lock(&mutex1);
  printf("Thread 3 acquired mutex1\n");

  // Release mutexes
  pthread_mutex_unlock(&mutex1);
  printf("Thread 3 released mutex1\n");
  pthread_mutex_unlock(&mutex3);
  printf("Thread 3 released mutex3\n");

  return NULL;
}
