#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define true 1
#define false 0

const int SECOND = 1000;

/* Functions */
void *cpu_intensive_thread();
void bubble_sort(int *, int);
void *io_intensive_thread();

/* Shared between threads */
double completeness = 0.0;
pthread_mutex_t lock_completeness;
pthread_t tid[2];

int array_size;

int main(int argc, char *argv[]) {
  int n, err;
  if (argc < 2) {
    printf("invalid arguments, should use:\n%s [size]\n", argv[0]);
    return -1;
  }
  if (pthread_mutex_init(&lock_completeness, NULL) != 0) {
    printf("\n mutex init failed\n");
    return 1;
  }

  n = atoi(argv[1]);
  array_size = n;

  err = pthread_create(&(tid[0]), NULL, &cpu_intensive_thread, NULL);
  if (err != 0)
    printf("\ncan't create thread :[%s]", strerror(err));

  err = pthread_create(&(tid[1]), NULL, &io_intensive_thread, NULL);
  if (err != 0)
    printf("\ncan't create thread :[%s]", strerror(err));

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_mutex_destroy(&lock_completeness);
  return 0;
}

/* CPU intensive thread */
void *cpu_intensive_thread() {
  int *vector;
  int n = array_size;
  int i;

  printf("[DEBUG] starting cpu_intensive_thread\n");
  vector = malloc(n * sizeof(int));
  srand(time(NULL));

  for (i = 0; i < n; i++)
    vector[i] = rand();

  bubble_sort(vector, n);

  free(vector);
  printf("[DEBUG] finishing cpu_intensive_thread\n");
  return NULL;
}

void bubble_sort(int vetor[], int n) {
  int k, j, aux;

  for (k = 1; k < n; k++) {
    for (j = 0; j < n - 1; j++) {
      if (vetor[j] > vetor[j + 1]) {
        aux = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = aux;
      }
    }
    pthread_mutex_lock(&lock_completeness);
    completeness = (double)k / (double)n;
    pthread_mutex_unlock(&lock_completeness);
  }
  pthread_mutex_lock(&lock_completeness);
  completeness = 1;
  pthread_mutex_unlock(&lock_completeness);
}

/* IO intensive thread */
void *io_intensive_thread() {
  double local_completeness = 0;
  printf("[DEBUG] starting io_intensive_thread\n");
  while (local_completeness < 1) {
    sleep(1);
    pthread_mutex_lock(&lock_completeness);
    local_completeness = completeness;
    pthread_mutex_unlock(&lock_completeness);
    printf("The job is %.2f%% complete\n", local_completeness * 100);
  }
  printf("[DEBUG] finishing io_intensive_thread\n");
  return NULL;
}
