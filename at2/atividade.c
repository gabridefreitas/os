/*
 * Nome: Gabriel de Freitas Adolfo
 * Registro acadêmico: XXXXXXX
 * Atividade: Cálculo de Números Perfeitos Usando Threads
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define NUM_THREADS 4
#define PERFECT_NUMBERS_NEEDED 5

static int current_number = 1;
static int perfect_count = 0;
static pthread_mutex_t mutex;

long get_time_ms(void) {
  struct timeval tv;

  gettimeofday(&tv, NULL);

  return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int isPrime(int num) {
  if (num < 2) return 0;
  if (num == 2) return 1;
  if (num % 2 == 0) return 0;

  for (int i = 3; i * i <= num; i += 2) {
    if (num % i == 0) return 0;
  }

  return 1;
}

int isPerfect(int n) {
  // Fórmula de Euclides-Euler: 2^(p-1) * (2^p - 1) onde 2^p - 1 é primo

  for (int p = 2; p <= 31; p++) {
    // Calcular 2^p - 1 (número de Mersenne)
    int mersenne = (1 << p) - 1;

    if (isPrime(mersenne)) {
      // Calcular 2^(p-1) * (2^p - 1)
      int perfect = (1 << (p - 1)) * mersenne;
      if (perfect == n) {
        return 1;
      }
      if (perfect > n) {
        break;
      }
    }
  }

  return 0;
}

void* thread_worker(void* arg) {
  long thread_id = (long)arg;
  int candidate;

  while (1) {
    if (perfect_count >= PERFECT_NUMBERS_NEEDED) {
      break;
    }

    pthread_mutex_lock(&mutex);
    candidate = current_number;
    current_number++;
    pthread_mutex_unlock(&mutex);

    if (isPerfect(candidate)) {
      pthread_mutex_lock(&mutex);
      if (perfect_count < PERFECT_NUMBERS_NEEDED) {
        printf("Thread %ld encontrou o número perfeito: %d\n", thread_id,
               candidate);
        perfect_count++;
      }
      pthread_mutex_unlock(&mutex);
    }
  }

  printf("Encerrando a thread %ld.\n", thread_id);
  pthread_exit(NULL);
}

int main() {
  pthread_t threads[NUM_THREADS];
  long start_time, end_time;
  int i;

  printf("=== Busca de Números Perfeitos com Threads ===\n");
  printf("Número de threads: %d\n", NUM_THREADS);
  printf("Números perfeitos a encontrar: %d\n\n", PERFECT_NUMBERS_NEEDED);

  if (pthread_mutex_init(&mutex, NULL) != 0) {
    fprintf(stderr, "Erro ao inicializar mutex!\n");
    exit(EXIT_FAILURE);
  }

  start_time = get_time_ms();

  for (i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&threads[i], NULL, thread_worker, (void*)(long)i) != 0) {
      fprintf(stderr, "Erro ao criar thread %d!\n", i);
      exit(EXIT_FAILURE);
    }
  }

  for (i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      fprintf(stderr, "Erro ao fazer join na thread %d!\n", i);
      exit(EXIT_FAILURE);
    }
  }

  end_time = get_time_ms();

  pthread_mutex_destroy(&mutex);

  printf("Tempo total de execução: %ld milissegundos\n", end_time - start_time);

  return EXIT_SUCCESS;
}